#include "tcp.hpp"

void		usage()
{
	std::cout << "Usage: ./tcp_chat <options>\n"
		"    options:\n"
		"\t-h, --host  hostname		<required>\n"
		"\t\tHostname/IP to listen in server mode or to connect to in client mode.\n\n"
		"\t-p, --port  portnumber		<required>\n"
		"\t\tTCP port to listen in server mode, or to connect to in client mode.\n\n"
		"\t-n, --name  nickname		<required for client>\n"
		"\t\tNickname to use in chat.\n\n"
		"\t-l, --listen			<required for server>\n"
		"\t\tTurn server mode on, if not specified - cliend mode.\n";
	exit(-1);
}

void		error(std::string str)
{
	std::cout << str << std::endl;
	exit(-1);
}

std::string	checkHostname(std::string &argVal, bool &host)
{
		//	If there is no argument for this flag and there is another flag coming right after it
	if (argVal == "-n" || argVal == "--name" || argVal == "-p" || argVal == "--port")
		error("\033[1;31mThere is no host.\033[0m");

	struct sockaddr_in	checkAddr;

		//	Check if the host is valid
	if (inet_pton(AF_INET, argVal.c_str(), &(checkAddr.sin_addr)) == 0)
		error("\033[1;31mInvalid host.\033[0m");

	host = true;
	return (argVal);
}

int		checkPort(std::string &argVal, bool &port)
{
	if (argVal == "-n" || argVal == "--name" || argVal == "-h" || argVal == "--host")
		error("\033[1;31mThere is no port number.\033[0m");

	int	portNum = atoi(argVal.c_str());

		//	Check if the port is valid
	if (portNum == 0)
		error("\033[1;31mInvalid port number.\033[0m");
	port = true;
	return (portNum);
}

void		readingArguments(User	*user, int argc, char **argv, int serOrCli)
{
	bool	port = false;				//	To check later if all flags have been set
	bool	host = false;
	bool	name = false;

	for (int i = 1; i < argc - 1; i++)
	{
		std::string	arg = argv[i];		//	Flag argument (e.g. "-p")
		std::string	argVal = argv[i + 1];	//	Flag argument value (e.g. "2000")

			/*	If current argument is a flag, then check if the next one isn't
				and take it as value. In case of the '--name/-n' flag also
				check if we are creating a client or a server via serOrCli variable	*/
		if (arg == "-h" || arg == "--host")
		{
			user->hostname = checkHostname(argVal, host);
			i++;
		}
		else if (arg == "-p" || arg == "--port")
		{
			user->setPortNumber(checkPort(argVal, port));
			i++;
		}
		else if ((arg == "-n" || arg == "--name") && serOrCli)
		{
			if (argVal == "-h" || argVal == "--host" || argVal == "-p" || argVal == "--port")
				error("\033[1;31mThere is no nickname.\033[0m");

			name = true;
			user->nickname = argVal;
			i++;
		}
	}
	if (!host || !port || (!name && serOrCli))
		usage();
}

int		serverOrClientFunc(int argc, char **argv)
{
	int	serverOrClient = 1;			//	1 - Client, 0 - Server
	std::string	arg;

	for (int i = 1; i < argc; i++)			//	Checking for server flag
	{
		arg = argv[i];
		if (arg == "-l" || arg == "--listen")
		{
			serverOrClient = 0;
			break;
		}
	}
	return (serverOrClient);
}
