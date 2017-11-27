#include "tcp.hpp"

int	main(int argc, char **argv)
{
	User	*user;		//	Pointer to one of the derived classes
	int	serverOrClient;

	if (argc < 6)		//	6 because we need at least [./a.out -p port -h host -l] arguments
		usage();

	serverOrClient = serverOrClientFunc(argc, argv);
	if (serverOrClient)	//	Point base class pointer to appropriate object
	{
		Client	*client = new Client;
		user = client;
	}
	else
	{
		Server	*server = new Server;
		user = server;
	}
	readingArguments(user, argc, argv, serverOrClient);

	user->init();
	delete user;
	return (0);
}
