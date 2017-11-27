#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <vector>
#include <arpa/inet.h>
#include <signal.h>

#define MAX_MSG_SIZE 100
#define TIMESTAMP_FORMAT "\033[1;33m[2017/6/10_15:44:13] \033[0m\0"

class	User
{
private:
	int			portNumber;

public:
	int			socketSD;
	char			buffer[MAX_MSG_SIZE];
	std::string		hostname;
	std::string		nickname;
	struct sockaddr_in	servAddr;
	struct sockaddr_in	clientAddr;

	int			getPortNumber();
	void			setPortNumber(int portNum);
	virtual void		init() = 0;
	User();
	virtual ~User();
};

void	error(std::string str);

#endif	//	USER_HPP
