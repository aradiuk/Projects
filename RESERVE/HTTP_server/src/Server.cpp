#include "http.hpp"
#include <sstream>

void	Server::init()
{
	int	on = 1;
	signal(SIGUSR1, reloadConfig);

		//	Fill structure and open socket depending on IP version
	if (inet_pton(AF_INET, getListenAddr().c_str(), &(servAddrV4.sin_addr)) == 1)		//	Handle IPv4
	{
		setIPVersion(4);
		servAddrV4.sin_family = AF_INET;
		servAddrV4.sin_port = htons(getPort());
		memset((void *)servAddrV4.sin_zero, '\0', sizeof(servAddrV4.sin_zero));
		listenSD = socket(AF_INET, SOCK_STREAM, 0);
	}
	else if (inet_pton(AF_INET6, getListenAddr().c_str(), &(servAddrV6.sin6_addr)) == 1)	//	Handle IPv4
	{
		setIPVersion(6);
		servAddrV6.sin6_family = AF_INET6;
		servAddrV6.sin6_port = htons(getPort());
		listenSD = socket(AF_INET6, SOCK_STREAM, 0);
	}
	if (listenSD == -1)
		error("Error while opening a socket for listening");
	if (setsockopt(listenSD, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)		//	Set socket to 'reuseable'
		error("Error while setting socket option");
	if (ioctl(listenSD, FIONBIO, (char *)&on) == -1)					//	Don't wait on 'accept()'
		error("ioctl() failed.");

		//	Bind socket with appropriate structure depenging on IP version
	if (getIPVersion() == 4 && bind(listenSD, (struct sockaddr *)&servAddrV4, sizeof(servAddrV4)) == -1)
		error("Error while binding the address4 to the socket");
	else if (getIPVersion() == 6 && bind(listenSD, (struct sockaddr *)&servAddrV6, sizeof(servAddrV6)) == -1)
		error("Error while binding the address6 to the socket");

	if (listen(listenSD, 32) == -1)
		error("Error while marking the socket as passive");

		//	Setting up eventfd and initialise listening socket pollfd struct
	termPoll.fd = eventfd(0, 0);
	termPoll.events = POLLIN;
	listeningSocket.fd = listenSD;
	listeningSocket.events = POLLIN;
}

void	Server::listenForRequests()
{
		/*	Create initial threads and wait till they are joined,
			which happens only if threads terminate and this happens
			when SIGUSR1 signal is received. After that clear everything,
			parse config file, initialise new listening socket and go to
			the start of the cycle			*/
	while (1)
	{
		this->threads = new pthread_t[numOfThreads];
		pthread_mutex_init(&mutex, 0);
		this->exitThreads = false;

		for (int i = 0; i < getNumOfThreads(); ++i)
			pthread_create(&threads[i], 0, serverWork, (void *)this);

		for (int i = 0; i < getNumOfThreads(); ++i)
			pthread_join(threads[i], 0);

		delete this->threads;
		pthread_mutex_destroy(&mutex);
		close(listenSD);
		close(termPoll.fd);
		parseConfig(this);
		this->init();
	}
}

void	acceptConnection(Server *server, std::vector<pollfd> &fds, int *acceptedSocket)
{
	struct sockaddr_in	clientAddrV4;
	struct sockaddr_in6	clientAddrV6;
	socklen_t		len;

	if (server->getIPVersion() == 4)
		len = sizeof(clientAddrV4);
	else if (server->getIPVersion() == 6)
		len = sizeof(clientAddrV6);

	pthread_mutex_lock(&server->mutex);
	do
	{
		pollfd	acceptSD;

		if (server->getIPVersion() == 4)
			*acceptedSocket = accept(server->listenSD, (struct sockaddr *)&clientAddrV4, &len);
		else if (server->getIPVersion() == 6)
			*acceptedSocket = accept(server->listenSD, (struct sockaddr *)&clientAddrV6, &len);
		if (*acceptedSocket == -1)
		{
			if (errno != EWOULDBLOCK)						//	EWOULDBLOCK means operation would block, but it doesn't because of ioctl()
				error("Error while accept()'ing a connection");
			pthread_mutex_unlock(&server->mutex);
			return;
		}

			//	Add a new connection to poll vector
		acceptSD.fd = *acceptedSocket;
		acceptSD.events = POLLIN;
		acceptSD.revents = 0;
		fds.push_back(acceptSD);
	}
	while (*acceptedSocket != -1);
	pthread_mutex_unlock(&server->mutex);
}

void	requestAndResponse(std::vector<pollfd>::iterator fdsIter, Request *request, Response *response, Server *server)
{
	char			buffer[BUFF_SIZE];
	int			received;
	std::string		receivedRequest;

		//	Read request into buffer and then add to a string 'receivedRequest'
	do {
		received = recv(fdsIter->fd, buffer, sizeof(buffer) - 1, 0);
		if (received == -1)
			error("Error while receiving a request.");

		buffer[received] = '\0';
		receivedRequest += buffer;
	} while(received == BUFF_SIZE);

		//	Parse request
	if (parseRequest(request, receivedRequest) == false)
	{
		response->setStatusCode(400);
		response->setStatusText("Bad Request");
	}
	else
		response->composeFilePath(request, server);

		//	Compose a response to the request
	response->respond(request, server, fdsIter->fd);
}

void	*Server::serverWork(void *serv)
{
	Server			*server = (Server *)serv;
	Request			*request = new Request;
	Response		*response = new Response;
	int			acceptedSocket;
	bool		terminatePoll = false;
	std::vector<pollfd>	fds;

	fds.push_back(server->termPoll);
	fds.push_back(server->listeningSocket);

	while (1)
	{
			//	Terminate thread if SIGUSR1 signal was received (it sets exitThreads to 'true')
		if (server->exitThreads == true)
		{
			delete request;
			delete response;
			for (auto it = fds.begin(); it != fds.end(); ++it)
				if (it->fd != -1)
					close(it->fd);

			pthread_exit(serv);
		}

			//	Accept connection according to IP version
		if (poll(&(fds.front()), fds.size(), -1) == -1)
			error("pollfd() failed.");

		std::vector<pollfd>::iterator fin = fds.end();
		for (std::vector<pollfd>::iterator fdsIter = fds.begin(); fdsIter != fin; ++fdsIter)
		{
			if (fdsIter->revents == 0)						//	Continue if no events received on this fd
				continue;
			if (fdsIter->fd == server->termPoll.fd && fdsIter->revents == POLLIN)
			{
				terminatePoll = true;
				break;
			}
			if (fdsIter->fd == server->listenSD)					//	Accept connections by listening socket
			{
				acceptConnection(server, fds, &acceptedSocket);
			}
			else if (fdsIter->fd != -1)
			{
				requestAndResponse(fdsIter, request, response, server);

				request->clear();
				response->clear();
				close(fdsIter->fd);
				fdsIter->fd = -1;
			}
		}
		if (terminatePoll)
			break;

			//	Clear vector from finished connections
		for (auto it = fds.begin(); it != fds.end(); )
		{
			if (it->fd == -1)
				it = fds.erase(it);
			else
				++it;
		}
	}
	delete request;
	delete response;
	pthread_exit(serv);
}

void	Server::setListenAddr(std::string const & str)
{
	this->listenAddr = str;
}

void	Server::setRootDir(std::string const & str)
{
	this->rootDir = str;
}

void	Server::setMimeTypes()
{
	std::ifstream	fileStream;
	std::string	line;

		//	Open '/etc/mime.types' file and read it into a string
	fileStream.open(MIMETYPES);
	if (!fileStream.is_open())
		error("Couldn't open '/etc/mime.types'");

	while (std::getline(fileStream, line))
		mimeTypes += line + "\n";
	fileStream.close();
}

std::string	Server::getMimeType(std::string const & ext) const
{
	std::stringstream	strStream;
	std::string		line;
	std::string		type = "";

	if (ext == "")										//	File has no extension
		return ("application/octet-stream");

	strStream << mimeTypes;

		/*	Read mimeTypes string looking for appropriate MIME. If there is a '/'
			symbol in a line, then we remember it as 'type' string and look through
			next lines comparing it with file's extension.		*/
	while (strStream >> line)
	{
		if (line[0] == '#')								//	If line is commented
			continue;
		if (line.find("/") != std::string::npos)
			type = line;
		else if (line == ext)
			return (type);
		line.clear();
	}
	return ("application/octet-stream");
}

void	Server::setPort(int p)
{
	this->port = p;
}

void	Server::setNumOfThreads(int n)
{
	this->numOfThreads = n;
}

void	Server::setIPVersion(int i)
{
	this->ipVersion = i;
}

std::string	Server::getListenAddr() const
{
	return (this->listenAddr);
}

std::string	Server::getRootDir() const
{
	return (this->rootDir);
}

int	Server::getPort() const
{
	return (this->port);
}

int	Server::getNumOfThreads() const
{
	return (this->numOfThreads);
}

int	Server::getIPVersion() const
{
	return (this->ipVersion);
}
