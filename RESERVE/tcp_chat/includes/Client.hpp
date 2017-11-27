#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "User.hpp"

class	Client : public User
{
public:
	virtual void	init();
	void		createThreads();
	Client();
	~Client();
};

#endif	// CLIENT_HPP
