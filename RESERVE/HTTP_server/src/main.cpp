#include "http.hpp"

Server *server;

void	reloadConfig(int signum)					//	Handling USERSIG1
{
	if (signum == SIGUSR1)
	{
		uint64_t	val = 1;

		if (write(server->termPoll.fd, &val, sizeof(uint64_t)) == -1)
			error("Error while writing to eventfd");
		server->exitThreads = true;
	}
}

void	error(std::string str)
{
	std::cout << str << std::endl;
	exit(-1);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " config.xml\n";
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		close(fd);
		error("Couldn't open 'config.xml'");
	}
	close(fd);

	server = new Server;
	server->confligFile = argv[1];
	server->defNumOfThreads = sysconf(_SC_NPROCESSORS_ONLN);	//	Maximum allowed number of threads
	parseConfig(server);
	server->setMimeTypes();
	server->init();
	server->listenForRequests();
}
