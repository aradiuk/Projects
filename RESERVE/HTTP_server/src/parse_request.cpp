#include "http.hpp"
#include <sstream>
#include <vector>

void 	decodeURI(std::string & uri)
{
	size_t			pos;
	std::stringstream	stream;
	int			decimalCode;

		/*	If unicode characters were found substr them (only numbers, e.g. %20 --> 20)
			and put them into stream as hex characters. After receiving them from
			stream as decimal, use it as char to replace unicode	*/
	while ((pos = uri.find("%")) != std::string::npos)
	{
		stream << std::hex << uri.substr(pos + 1, 2).c_str();
		stream >> decimalCode;
		uri.replace(pos, 3, 1, decimalCode);
	}
}

bool	checkMethod(std::string const & str)
{
	std::vector<std::string>		legalMethods;
	std::vector<std::string>::iterator	it;

	legalMethods.push_back("GET");
	legalMethods.push_back("POST");
	legalMethods.push_back("HEAD");
	legalMethods.push_back("PUT");
	legalMethods.push_back("DELETE");
	legalMethods.push_back("CONNECT");
	legalMethods.push_back("OPTIONS");
	legalMethods.push_back("PATCH");

	for (it = legalMethods.begin(); it != legalMethods.end(); ++it)
	{
		if (str == *it)
			return (true);
	}
	return (false);
}

bool	checkProtocol(std::string const & str)
{
	std::vector<std::string>		legalProtocols;
	std::vector<std::string>::iterator	it;

	legalProtocols.push_back("HTTP/0.9");
	legalProtocols.push_back("HTTP/1.0");
	legalProtocols.push_back("HTTP/1.1");
	legalProtocols.push_back("HTTP/2.0");

	for (it = legalProtocols.begin(); it != legalProtocols.end(); ++it)
	{
		if (str == *it)
			return (true);
	}
	return (false);
}

bool	parseRequestLine(Request *request, std::string const & str)
{
	std::string		requestLineArgs[3];
	std::stringstream	strStream;
	int			numOfWords = 0;

	request->setProtVersion(SERVER_PROT);			// Set default response protocol

	strStream << str;
	while (strStream >> requestLineArgs[0])			//	Check number of "words" in request line
		++numOfWords;
	if (numOfWords != 3)
		return (false);

		/*	Using stringstream to separate "words" from request
			line and put them into a string array		*/
	strStream.clear();
	strStream << str;
	for (int i = 0; i < 3; ++i)
		strStream >> requestLineArgs[i];

	if (!checkMethod(requestLineArgs[0]))			//	Check if method is one of the allowed HTTP methods
		return (false);
	request->setMethod(requestLineArgs[0]);

	if (requestLineArgs[1] == "/")
		requestLineArgs[1] = "/index.html";
	else
		decodeURI(requestLineArgs[1]);

	request->setRequestURI(requestLineArgs[1]);

	if (!checkProtocol(requestLineArgs[2]))			//	Check if protocol is one of the allowed HTTP protocols
		return (false);
	request->setProtVersion(requestLineArgs[2]);

	return (true);
}

bool	parseRequest(Request *request, std::string content)
{
	std::string	requestLine;
	std::string	remains;
	std::string	line;
	size_t		requestLineEnd;
	size_t		lineEnd;

	requestLineEnd = content.find("\r\n");
	if (requestLineEnd == std::string::npos)
		return (false);

	requestLine = content.substr(0, requestLineEnd);	//	Separate first line of the request
	if (content.size() < requestLineEnd + 2)
		return (false);

	remains = content.substr(requestLineEnd + 2);		//	+2 for "\r\n"
	if (remains == "")
		return (false);

	if (parseRequestLine(request, requestLine) == false)
		return (false);

	while (1)
	{
		lineEnd = remains.find("\r\n");			//	Searching for the end of each header line
		if (lineEnd == std::string::npos)
			break;

		line = remains.substr(0, lineEnd);		//	Substracting a line from the request
		if (line.empty())
			break;

		request->insertField(line);			//	Filling the with header information

		remains = remains.substr(lineEnd + 2);		//	"Removing" used line
		if (remains.empty())
			break;
	}
	if (request->getMethod() == "POST")			//	Get message body if it is not a 'GET' request
		request->setMessageBody(remains);
	return (true);
}
