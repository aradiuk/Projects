#include "Server.hpp"

Server::Server()
{}

Server::~Server()
{}

void	Server::init()
{
	int	on = 1;

	listenSD = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSD == -1)
		error("\033[1;31mError while opening server socket.\033[0m");
	if (setsockopt(listenSD, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
		error("\033[1;31mError while setting socket option.\033[0m");
	if (ioctl(listenSD, FIONBIO, (char *)&on) == -1)				//	Set socket to be nonblocking when accepting new connections
	{
		std::cout << "\033[1;31m\nioctl() call failed.\033[0m" << std::endl;
		close(listenSD);
		exit(-1);
	}

		//	Initialising sockaddr_in structure
	servAddr.sin_family = AF_INET;							//	Using internet protocol
	servAddr.sin_addr.s_addr = inet_addr(hostname.c_str());
	servAddr.sin_port = htons(getPortNumber());
	memset((void *)servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero)); 					//	Zeroing sin_zero array in sockaddr_in structure

	if (bind(listenSD, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
		error("\033[1;31mError while binding the address to the socket.\033[0m");
	if (listen(listenSD, 32) == -1)
		error("\033[1;31mError while marking a socket as passive.\033[0m");

	commands();									//	Show all possible commands
	createThreads();
	close(listenSD);
}

void	Server::createThreads()
{
	pthread_t	threads[2];

	pthread_create(&threads[0], 0, sendCommand, (void *)this);			//	Thread for using server commands
	pthread_create(&threads[1], 0, acceptConnections, (void *)this);		//	Thread for receiving logs from clients

	for (int i = 0; i < 2; i++)
		pthread_join(threads[i], 0);
}

void	*Server::sendCommand(void *serv)
{
	Server		*server = (Server *)serv;
	std::string	readInput;
	size_t		argPos;								//	= npos if there is no command in readInput,
											//	otherwise points to the first symbol of the command

		/*	Heavy use of determining a starting position of a command with
			string::find and deriving a substring from readInput starting
			from the end of the command plus one space			*/
	while (1)
	{
			//	Get command input
		readInput.clear();
		if (!std::getline(std::cin, readInput))	//	Check if we came across EOF
			error("\033[1;31mStdin on the server was closed.\033[0m\n");

			//	A bunch of "if else"s, created to read a command and launch an appropriate fucntion
		if (readInput.find("/showusers") != std::string::npos)			//	'/showusers'
		{
			server->showUsers(server);
		}
		else if ((argPos = readInput.find("/kickuser ")) != std::string::npos)	//	'/kickuser'
		{
			server->kickUser(server, readInput.substr(argPos + strlen("/kickuser ")));
		}
		else if ((argPos = readInput.find("/banuser ")) != std::string::npos)	//	'/banuser'
		{
			server->banUser(server, readInput.substr(argPos + strlen("/banuser ")));
		}
		else if ((argPos = readInput.find("/banhost ")) != std::string::npos)	//	'/banhost'
		{
			server->banHost(server, readInput.substr(argPos + strlen("/banhost ")));
		}
		else if ((argPos = readInput.find("/unbanuser ")) != std::string::npos)	//	'/unbanuser'
		{
			server->unbanUserOrHost(readInput.substr(argPos + strlen("/unbanuser ")), "");
		}
		else if ((argPos = readInput.find("/unbanhost ")) != std::string::npos)	//	'/unbanhost'
		{
			server->unbanUserOrHost("", readInput.substr(argPos + strlen("/unbanhost ")));
		}
		else if ((argPos = readInput.find("/getbanlist")) != std::string::npos)	//	'/getbanlist'
		{
			server->getBanList();
		}
		else									//	Not known command or just poorly used
		{
			std::cout << "\033[94mNo command '" << readInput << "' or wrong usage.\033[0m\n\n";
		}
	}
	pthread_exit(serv);
}


void	*Server::acceptConnections(void *serv)
{
	Server	*server = (Server *)serv;
	pollfd	initialSD;
	bool	endServer = false;

	initialSD.fd = server->listenSD;					//	Initial (listening) socket
	initialSD.events = POLLIN;

	server->fds.push_back(initialSD);
	do
	{
		pthread_mutex_lock(&server->mutex);
		if (poll(&(server->fds.front()), server->fds.size(), 1) == -1)		//	Initialising a poll
			error("\033[1;31mpoll() call failed.\033[0m");

		std::vector<pollfd>::iterator fdsEnd = server->fds.end();		//	Setting end of the vector for this step
		for (std::vector<pollfd>::iterator fdsIter = server->fds.begin(); fdsIter != fdsEnd; ++fdsIter)
		{
			if (fdsIter->revents == 0)					//	No events occured on a client's side
				continue;
			if (fdsIter->revents != POLLIN)					//	Unexpected value of revents
			{
				endServer = true;
				server->disconnectClient(server, fdsIter);
				break;
			}
			if (fdsIter->fd == server->listenSD)
			{
				if (server->listeningSocket(server, endServer))
					break;
			}
			else if (fdsIter->fd != -1)
				server->clientSocket(server, &fdsIter, fdsEnd);
		}
		server->clearVector(&server->fds);					//	Clear vector from closed connections
		pthread_mutex_unlock(&server->mutex);
	} while(endServer == false);

		//	Close all sockets that have not been closed yet
	for (std::vector<pollfd>::iterator fdsIter = server->fds.begin(); fdsIter != server->fds.end(); ++fdsIter)
		if (fdsIter->fd >= 0)
			close(fdsIter->fd);
	pthread_exit(serv);
}

bool	Server::listeningSocket(Server *server, bool &endServer)
{
	std::string	message;
	socklen_t	len;
	pollfd		newConnection;
	info		clientIn;
	bool		newElement = false;

	do
	{
		len = sizeof(clientAddr);

		socketSD = accept(server->listenSD, (struct sockaddr *)&clientAddr, &len);
		if (socketSD == -1)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cout << "\033[1;31maccept() call failed.\033[0m\n";
				endServer = true;
			}
			break;
		}

		if (recv(socketSD, buffer, sizeof(buffer), 0) == -1)
			error("\033[1;31mError while receiving 'connected' message.\033[0m");

		clientIn.nickname = buffer;
		clientIn.address = 	inet_ntoa(clientAddr.sin_addr);
		if (nameTaken(server, clientIn.nickname, socketSD))
			continue;
		if (banned(clientIn.nickname, "") || banned("", clientIn.address))
		{
			unicastMesage(socketSD, "\nbanned\n");
			close(socketSD);
			continue;
		}
			//	Initialising vector element for new connection
		newConnection.fd = socketSD;
		newConnection.events = POLLIN;
		newConnection.revents = 0;
		server->fds.push_back(newConnection);


			//	Initialising new map element for client's info
		server->clientInfo.insert(std::pair<int, struct info>(socketSD, clientIn));

		message =  "\033[1;32m============>   " + clientIn.nickname + " connected\033[0m\n";
		broadcast(&server->fds, message, server->fds.end());
		memset((void *)buffer, '\0', sizeof(buffer));
		newElement = true;
	} while(socketSD != -1);
	return (newElement);
}

void	Server::clientSocket(Server *server, std::vector<pollfd>::iterator *fdsIter, std::vector<pollfd>::iterator fdsEnd)
{
	int				received;
	std::map<int, struct info>::iterator mapIter;
	std::string			broadcastMessage;
	bool				closeConnection = false;

	do
	{
		received = recv((*fdsIter)->fd, buffer, sizeof(buffer), 0);
		if (received == 0)							//	Connection closed by a client
		{
			broadcastMessage = "\033[1;32m============>   " + (server->clientInfo.find((*fdsIter)->fd))->second.nickname + " left.\033[0m\n";
			disconnectClient(server, *fdsIter);
			broadcast(&server->fds, broadcastMessage, server->fds.end());
			closeConnection = true;
			break;
		}
		if (received == -1)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cout << "\033[1;31mrecv() call failed.\033[0m" << std::endl;
				closeConnection = true;
			}
			break;
		}

		clientWork(buffer, &server->fds, fdsEnd);
		memset((void *)buffer, '\0', sizeof(buffer));

	} while(read((*fdsIter)->fd, buffer, 0) > 0);

	if (closeConnection)
		disconnectClient(server, *fdsIter);
}

void	Server::clientWork(char buffer[], std::vector<struct pollfd> *fds, std::vector<pollfd>::iterator fdsEnd)
{
	char	timeStamp[TIMESTAMP_SIZE];
	time_t	timeMark;

		// Composing a string with date/time information in format [2017/6/10_15:44:13]
	timeMark = time(0);
	strftime(timeStamp, sizeof(timeStamp), "\033[1;33m[%Y/%d/%m_%H:%M:%S] \033[0m\0", localtime(&timeMark));
	std::string message = timeStamp;
	message += buffer;								//	Attaching client's message to the timestamp
	message += "\n";
	broadcast(fds, message, fdsEnd);
}
