#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

void	parseError(std::string str, xmlDocPtr doc);
void	parseConfig(Server *server);
void	error(std::string str);
bool	parseRequest(Request *request, std::string content);

#endif	//	HTTP_HPP
