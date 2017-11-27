#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "http.hpp"
#include <map>
#include <sys/stat.h>
#include <fstream>

#define SERVER_PROT "HTTP/1.1"

class	Response
{
private:
	std::string	protVersion;
	int		statusCode;
	std::string	statusText;
	std::string	statusLine;
	std::string	messageBody;
	std::map<std::string, std::string> responseForm;

public:
	std::string	fullPath;
	std::string	responseMessage;

	Response();
	void		setProtVersion(std::string const & str);
	void		setStatusCode(int c);
	void		setStatusText(std::string const & str);
	void		setStatusLine(std::string const & str);
	void		setMessageBody(std::string const & str);
	std::string	getProtVersion() const;
	int		getStatusCode() const;
	std::string	getStatusText() const;
	std::string	getStatusLine() const;
	std::string	getMessageBody() const;
	std::string	encodeURI(std::string const & str);

	void		insertField(std::string const & key, std::string const & value);
	void		composeFilePath(Request *request, Server *server);
	void		respond(Request *request, Server *server, int clientSocket);
	void		responseHeaders(Request *request, Server *server);
	void		composeGetResponseBody();
	void		composeResponseMessage();
	// void		composePostResponseBody();	//	For future use
	bool		validateRequest(Request *request);
	bool		fileExists();
	bool		fileAccessible(std::string const & str);
	void		clear();
};

#endif	//	RESPONSE_HPP
