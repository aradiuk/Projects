#include "Client.hpp"

static void 	*sendMessage(void *client);
static void 	*receiveMessage(void *client);

Client::Client()
{}

Client::~Client()
{}

void	Client::init()
{
	int		sent;
	std::string	message;

	socketSD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketSD == -1)
		error("\033[1;31m\nError while opening client socket.\033[0m");

		//	Initialise sockaddr_in structure
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = inet_addr(hostname.c_str());
	clientAddr.sin_port = htons(getPortNumber());

		//	Initiate a connection to the socket
	if (connect(socketSD, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) == -1)
		error("\033[1;31m\nError while connecting to the server.\033[0m");

		//	Send  nickname of the client
	message = nickname;
	sent = send(socketSD, message.c_str(), message.size(), 0);
	if (sent == -1)
		error("\033[1;31m\nError while sending data to the server.\033[0m");

	createThreads();
	close(socketSD);
}

void	Client::createThreads()
{
	pthread_t	threads[2];

	pthread_create(&threads[0], 0, sendMessage, (void *)this);	//	Thread for sending messages to the server
	pthread_create(&threads[1], 0, receiveMessage, (void *)this);	//	Thread for receiving messages from the server

	for (int i = 0; i < 2; i++)
		pthread_join(threads[i], 0);
}

void 	*sendMessage(void *cl)
{
	int		sent;
	std::string	readInput;
	std::string	message;
	Client		*client = (Client *)cl;

	while (1)
	{
			//	Get input from the client
		readInput.clear();
		if (!std::getline(std::cin, readInput))			//	Check if we came across EOF (Ctrl + D)
			error("\033[1;31mStdin was closed.\033[0m\n");

			/*	Restrict messages, longer than MAX_MSG_SIZE, which is also the
				size of our buffer, taking into account	space for timestamp
				Composing message from client's nickname and his input
				which is going to be sent to the server			*/
		message = "\033[1;36m" + client->nickname + "\033[0m" + ": " + readInput;
		if (message.size() >= sizeof(client->buffer) - sizeof(TIMESTAMP_FORMAT))
		{
			std::cout << "\033[1;35mMessage is too long. Try again.\033[0m\n\n";
			continue;
		}
		sent = write(client->socketSD, message.c_str(), message.size());
		if (sent == -1)
			error("\033[1;31mError while sending data to the server.\033[0m");
	}
	pthread_exit(cl);
}

void	*receiveMessage(void *cl)
{
	int		received;
	std::string	message;
	Client		*client = (Client *)cl;

	while (1)
	{
			//	Receive message from the server
		received = recv(client->socketSD, client->buffer, sizeof(client->buffer), 0);
		if (received == -1)
			error("\033[1;31mError while receiving data from server.\033[0m");
		else if (received == 0)
			error("\033[1;31mConnection closed.\033[0m");

		message = client->buffer;

			//	Check for some 'special' messages ("handmade signals")
		if (message == "\nclose\n")				//	Client was kicked by the server
			error("\033[1;31mConnection closed.\033[0m");
		else if (message == "\nnametaken\n")			//	There is a client with that name already
			error("\033[1;31mThis name is taken.\033[0m");
		else if (message == "\nbanned\n")			//	Self-explanatory...
			error("\033[1;31mYou are banned.\033[0m");

		std::cout << client->buffer;
		memset((void *)client->buffer, '\0', sizeof(client->buffer));
	}
	pthread_exit(cl);
}
