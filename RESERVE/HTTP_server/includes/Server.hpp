#ifndef SERVER_HPP
#define SERVER_HPP

#include "http.hpp"
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <poll.h>
#include <vector>
#include <sys/eventfd.h>

#define BUFF_SIZE 1024
#define MIMETYPES "/etc/mime.types"

void	reloadConfig(int signum);

class	Server
{
private:
	std::string		listenAddr;
	std::string		rootDir;
	std::string		mimeTypes;
	int			port;
	int			numOfThreads;
	int			ipVersion;

public:
	pthread_t		*threads;
	pollfd			termPoll;
	pollfd			listeningSocket;
	std::string		confligFile;
	int			defNumOfThreads;
	int			listenSD;
	struct sockaddr_in	servAddrV4;
	struct sockaddr_in6	servAddrV6;
	pthread_mutex_t		mutex;
	bool			exitThreads = false;

	void			setListenAddr(std::string const & str);
	void			setRootDir(std::string const & str);
	void			setMimeTypes();
	void			setPort(int p);
	void			setNumOfThreads(int n);
	void			setIPVersion(int i);
	std::string		getListenAddr() const;
	std::string		getRootDir() const;
	std::string		getMimeType(std::string const & ext) const;
	int			getPort() const;
	int			getNumOfThreads() const;
	int			getIPVersion() const;
	void			init();
	void			listenForRequests();
	static void		*serverWork(void *server);
};

#endif	//	SERVER_HPP
