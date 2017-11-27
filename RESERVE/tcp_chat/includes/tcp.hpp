#ifndef TCP_H
#define tcp_chat

#include "User.hpp"
#include "Server.hpp"
#include "Client.hpp"

void	usage();
void	error(std::string str);
void	readingArguments(User *user, int argc, char **argv, int serOrCli);
int	serverOrClientFunc(int argc, char **argv);

#endif	//	TCP_H
