#ifndef SERVER_HPP
#define SERVER_HPP

#include "User.hpp"
#include <map>
#include <fstream>

struct	info
{
	std::string	nickname;
	std::string	address;
};

class	Server : public User
{
public:
	pthread_mutex_t			 mutex;
	int				listenSD;
	std::vector<struct pollfd>	fds;
	std::map<int, struct info>	clientInfo;
	virtual void			init();
	static void			*sendCommand(void *server);
	static void			*acceptConnections(void *server);
	void				commands();
	void				createThreads();
	void				unicastMesage(int socket, std::string message);
	bool				nameTaken(Server *server, std::string &nickname, int socketSD);
	void				clientWork(char	buffer[], std::vector<struct pollfd> *fds, std::vector<pollfd>::iterator fdsEnd);
	bool				listeningSocket(Server *server, bool &endServer);
	void				clientSocket(Server *server, std::vector<pollfd>::iterator *fdsIter, std::vector<pollfd>::iterator fdsEnd);
	void				clearVector(std::vector<struct pollfd> *fds);
	void				broadcast(std::vector<struct pollfd> *fds, std::string message, std::vector<pollfd>::iterator fdsEnd);
	void				disconnectClient(Server *server, std::vector<pollfd>::iterator &fdsIter);
	void				showUsers(Server *server);
	void				kickUser(Server *server, std::string username);
	void				kickHost(Server *server, std::string address);
	void				banUser(Server *server, std::string username);
	void				unbanUserOrHost(std::string username, std::string address);
	void				banHost(Server *server, std::string address);
	bool				banned(std::string username, std::string address);
	void				getBanList();
	Server();
	~Server();
};

#endif	//	SERVER_HPP
