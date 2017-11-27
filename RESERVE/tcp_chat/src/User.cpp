#include "User.hpp"

User::User()
{}

User::~User()
{}

int	User::getPortNumber()
{
	return (portNumber);
}

void	User::setPortNumber(int port)
{
	portNumber = port;
}
