#include "Server.hpp"

void	Server::commands()
{
	std::cout << "Commands:\n"
			"/showusers - show currently connected users, with their names and IPs\n"
			"/kickuser <username> - kick the user from the chat\n"
			"/banuser <username> - ban the user from using the chat\n"
			"/unbanuser <username> - unban the user from the chat\n"
			"/banhost <host> - ban all users from the specified host to be connected\n"
			"/unbanhost <host> - unban host from the chat\n"
			"/getbanlist - show the list of banned users and/or hosts\n\n";
}

void	Server::unicastMesage(int socket, std::string message)
{
	int	sent;

		//	Send message to one of the clients, defined with socket
	sent = write(socket, message.c_str(), message.size());
	if (sent == -1)
		error("\033[1;31mError while sending a unicast message to the client.\033[0m");
}

bool	Server::nameTaken(Server *server, std::string &nickname, int socketSD)
{
	std::map<int, struct info>::iterator	mapIter;
	std::string				message;
	bool					taken = false;

		/*	Iterate through the map looking for particular nickname.
			Send 'nametaken' signal to the client if found.	*/
	for (mapIter = server->clientInfo.begin(); mapIter != server->clientInfo.end(); ++mapIter)
	{
		if (mapIter->second.nickname == nickname)
		{
			taken = true;
			unicastMesage(socketSD, "\nnametaken\n");
			close(socketSD);
			break;
		}
	}
	return (taken);
}

void	Server::showUsers(Server *server)
{
	int 					id = 1;
	std::map<int, struct info>::iterator	mapIter;

		//	Iterate through the map of clients outputting nickname and IP for each
	std::cout << "\033[94m" << server->clientInfo.size() << " users online:\033[0m" << std::endl;
	for (mapIter = server->clientInfo.begin(); mapIter != server->clientInfo.end(); ++mapIter)
	{
		std::cout << "\033[94m" << id++ << ": " << mapIter->second.nickname << " - ";
		std::cout << mapIter->second.address << "\033[0m" << std::endl;
	}
	std::cout << std::endl;
}

void	Server::kickUser(Server *server, std::string username)
{
	std::map<int, struct info>::iterator	mapIter;
	std::vector<pollfd>::iterator		fdsIter;
	std::string				broadcastMessage;

		/*	Iterate through the map of clients looking for a client with specified username,
			take its FD value and then iterate through the vector of pollfd structures looking
			for the one with that FD. Send a 'close' signal to that client and rewrite FD,
			so the client could be erased from the vector. Also erase client's info from the map
			and broadcast a message to every other client.	*/

	pthread_mutex_lock(&server->mutex);
	for (mapIter = server->clientInfo.begin(); mapIter != server->clientInfo.end(); ++mapIter)
	{
		if (mapIter->second.nickname == username)
		{
			for (fdsIter = server->fds.begin(); fdsIter != server->fds.end(); ++fdsIter)
			{
				if (fdsIter->fd == mapIter->first)
				{
					unicastMesage(fdsIter->fd, "\nclose\n");
					close(fdsIter->fd);
					fdsIter->fd = -1;
					break;
				}
			}
			server->clientInfo.erase(mapIter);
			broadcastMessage = "\033[1;32m============>   " + username + " left.\033[0m\n";
			std::cout << "\033[94mUser '" << username << "' has been kicked.\033[0m\n";
			broadcast(&server->fds, broadcastMessage, server->fds.end());
			pthread_mutex_unlock(&server->mutex);
			return ;
		}
	}
	pthread_mutex_unlock(&server->mutex);
	std::cout << "\033[94mNo user named '" << username << "' is online.\033[0m\n\n";
}

void	Server::kickHost(Server *server, std::string address)
{
	std::map<int, struct info>::iterator	mapIter;
	std::vector<pollfd>::iterator		fdsIter;
	std::string				broadcastMessage;

		/*	Pretty much the same as 'kickUser' function, but this looks for the specified
			host address in the map and doesn't stop after finding one client with that host	*/

	pthread_mutex_lock(&server->mutex);
	for (mapIter = server->clientInfo.begin(); mapIter != server->clientInfo.end();)
	{
		if (mapIter->second.address == address)
		{
			for (fdsIter = server->fds.begin(); fdsIter != server->fds.end(); ++fdsIter)
			{
				if (fdsIter->fd == mapIter->first)
				{
					unicastMesage(fdsIter->fd, "\nbanned\n");
					close(fdsIter->fd);
					fdsIter->fd = -1;
					break;
				}
			}
			mapIter = server->clientInfo.erase(mapIter);	//	Preserve iterator
		}
		else
		 	++mapIter;
	}
	pthread_mutex_unlock(&server->mutex);
}

void	Server::banUser(Server *server, std::string username)
{
	std::fstream	fileStream;

	if (banned(username, ""))					//	Check if the user isn't banned already
	{
		std::cout << "\033[94mUser '" << username << "' is banned already.\033[0m\n\n";
		return ;
	}

		//	Open banlist.txt containing banned users and hosts. Create if none exist
	fileStream.open("../banlist.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	if (!fileStream.is_open())
		error("\033[1;31mCouldn't open 'banlist.txt'.\033[0m");

	kickUser(server, username);					//	Kick user before banning
	fileStream << "U: " << username << std::endl;			//	Write a string of format "U: username" to a file
	std::cout << "\033[94mUser '" << username << "' has been banned.\033[0m\n\n";
	fileStream.close();
}

void	Server::banHost(Server *server, std::string address)
{
	std::fstream	fileStream;

		//	Check if host isn't banned already
	if (banned("", address))
	{
		std::cout << "\033[94mHost '" << address << "' has been banned already.\033[0m\n\n";
		return ;
	}
		//	Open banlist.txt containing banned users and hosts. Create if none exist
	fileStream.open("../banlist.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	if (!fileStream.is_open())
		error("\033[1;31mCouldn't open 'banlist.txt'.\033[0m");

	kickHost(server, address);					//	Kick all client's from specified host before banning
	fileStream << "H: " << address << std::endl;			//	Write a string of format "H: hostaddress" to a file
	std::cout << "\033[94m'" << address << "' has been banned.\033[0m\n\n";
	fileStream.close();
}

void	Server::unbanUserOrHost(std::string username, std::string address)
{
	std::fstream	fileOut;
	std::ofstream	fileIn;
	std::string	line;

		//	Check if user/host is really banned
	if (!banned(username, address))
	{
		std::cout << "\033[94muser/Host named '" << username + address << "' is not banned.\033[0m\n\n";
		return ;
	}

		//	Open banlist.txt containing banned users and hosts. Create if none exist
	fileOut.open("../banlist.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	if (!fileOut.is_open())
		error("\033[1;31mCouldn't open 'banlist.txt'.\033[0m");

		/*	Open 'unbanned.txt' temporary file which will contain every line from
			'banned.txt' except one. Create if none exist		*/
	fileIn.open("../unbanned.txt");
	if (!fileIn.is_open())
		error("\033[1;31mCouldn't open temporary buffer file.\033[0m");

		/*	Read 'banlist.txt' and write everything except the unbanned user/host
			to 'unbanned.txt' temporary fileOut			*/
	while (getline(fileOut, line))
	{
		if (username != "" && line.substr(0, 3) == "U: " && line.substr(3) == username)
			continue;
		else if (address != "" && line.substr(0, 3) == "H: " && line.substr(3) == address)
			continue;
		fileIn << line << std::endl;
	}
	std::cout << "\033[94mUser/Host named '" << username + address<< "' is no longer banned.\033[0m\n\n";

	fileOut.close();
	fileIn.close();
	remove("../banlist.txt");					//	Remove 'banlist.txt'
	rename("../unbanned.txt", "../banlist.txt");			//	Replace 'banlist.txt' with edited file 'unbanned.txt'
}

void	Server::getBanList()
{
	std::ifstream	fileIn;
	std::string	line;

		//	Open banlist.txt containing banned users and hosts. Create if none exist
	fileIn.open("../banlist.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	if (!fileIn.is_open())
		error("\033[1;31mCouldn't open 'banlist.txt' for reading.\033[0m");

	std::cout << "\033[94mBanned users/hosts(U/H):\033[0m\n";
	while (getline(fileIn, line))
	{
		std::cout << "\033[94m" << line << "\033[0m" << std::endl;
	}
	std::cout << std::endl;
}

bool	Server::banned(std::string username, std::string address)
{
	std::fstream	fileIn;
	std::string	line;

		//	Open banlist.txt containing banned users and hosts. Create if none exist
	fileIn.open("../banlist.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	if (!fileIn.is_open())
		error("\033[1;31mCouldn't open 'banlist.txt' for reading.\033[0m");

		/*	Read every line from 'banlist.txt' and check whether it contains
			the specified user/host - return true, otherwise - false	*/

	while (getline(fileIn, line))
	{
		if (username != "")
		{
			if (line.substr(0, 3) == "U: " && line.substr(3) == username)
			{
				fileIn.close();
				return (true);
			}
		}
		else if (address != "")
		{
			if (line.substr(0, 3) == "H: " && line.substr(3) == address)
			{
				fileIn.close();
				return (true);
			}
		}
	}
	fileIn.close();
	return (false);
}

void	Server::disconnectClient(Server *server, std::vector<pollfd>::iterator &fdsIter)
{
	std::map<int, struct info>::iterator mapIter;

		/*	Remove specified client's info from the map, close socket and set client's
			FD to -1 to be removed from pollfd vector later		*/
	close(fdsIter->fd);
	mapIter = server->clientInfo.find(fdsIter->fd);
	if (mapIter != server->clientInfo.end())
		server->clientInfo.erase(mapIter);
	fdsIter->fd = -1;
}

void	Server::broadcast(std::vector<struct pollfd> *fds, std::string message, std::vector<pollfd>::iterator fdsEnd)
{
	int	sent;

		//	Send specified message to all clients
	for (std::vector<pollfd>::iterator fdsIter = fds->begin() + 1; fdsIter != fdsEnd; ++fdsIter)
	{
		if (fdsIter->fd == -1)
			continue;
		sent = write(fdsIter->fd, message.c_str(), message.size());
		if (sent == -1)
			error("\033[1;31mError while sending data to the server.\033[0m");
	}
}

void	Server::clearVector(std::vector<struct pollfd> *fds)
{
		//	Remove 'marked'(with fd set to -1) vector elements
	for (std::vector<pollfd>::iterator fdsIter = fds->begin() + 1; fdsIter != fds->end(); )
	{
		if (fdsIter->fd == -1)
			fdsIter = fds->erase(fdsIter);			//	Preserve iterator
		else
			++fdsIter;
	}
}
