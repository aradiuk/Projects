#include "http.hpp"
#include <sstream>

Response::Response() : protVersion(""), statusCode(0), statusText(""),
		messageBody("")
{}

std::string	Response::encodeURI(std::string const & str)
{
	std::string		res = str;
	std::string		encodeCharacters = " \"\%<>#{}|\\^~[]`";	//	Unsafe characters
	std::stringstream	stream;
	int			decCode;
	std::string		hexCode;

		/*	Iterating through the string and encode all characters that are
			below 32 or over 126 on ASCII table, or are unsafe	*/
	for (size_t i = 0; i < res.size(); ++i)
	{
		decCode = res[i];
		if (decCode <= 31 || decCode >= 127 || encodeCharacters.find(res[i], 0) != std::string::npos)
		{
			stream << std::hex << decCode;
			stream >> hexCode;
			if (hexCode.size() == 1)
				hexCode.insert(0, "0");
			res.replace(i, 1, "%" + hexCode);
			stream.clear();
		}
	}
	return (res);
}

void	Response::composeFilePath(Request * request, Server * server)
{
	fullPath = server->getRootDir() + request->getRequestURI();
}

bool	Response::fileExists()
{
	struct stat buffer;

	return (stat(fullPath.c_str(), &buffer) == 0);
}

bool	Response::fileAccessible(std::string const & requestURI)
{
	std::ifstream file(fullPath.c_str());

		//	Check if file is accessible and no upper directory files are being accessed
	if (file.good() && requestURI.find("..") == std::string::npos)
		return (true);
	else
		return (false);
}

void	Response::composeGetResponseBody()
{
	std::ifstream	fileRequested;
	std::string	line;
	std::string	body;

	fileRequested.open(fullPath, std::ifstream::in | std::ifstream::binary);
	if (!fileRequested.is_open())
		error("Error while opening requested file.");
	while(std::getline(fileRequested, line))
		body += line + "\n";
	setMessageBody(body);
}

void	Response::responseHeaders(Request *request, Server *server)
{
	char		timeStamp[25];
	std::string	ext;
	std::string	mimeType;
	time_t		timeMark;

	timeMark = time(0);
	strftime(timeStamp, sizeof(timeStamp), "%a %b %e %H:%M:%S %Y", localtime(&timeMark));

		//	Adding elements to response headers map
	if (request->getMethod() == "POST")
		insertField("Location", encodeURI("http://" + request->getHeaderValue("Host") + request->getRequestURI()));
	insertField("Cache-Control", "no-cache");
	insertField("Date", timeStamp);
	insertField("Connection", "close");
	if (getStatusCode() == 200 || getStatusCode() == 201)
		insertField("Content-Type", server->getMimeType(request->getExtension(request->getRequestURI())));
	else	//	In case of some error plain text is sent to inform
		insertField("Content-Type", "text/plain");
	insertField("Content-Length", std::to_string(getMessageBody().size()));
}

bool	Response::validateRequest(Request * request)
{
	setStatusCode(0);
	setStatusText("");

	if (request->getMethod() != "GET" && request->getMethod() != "POST")
	{
		setStatusCode(405);
		setStatusText("Method Not Allowed");
	}
	else if (request->getProtVersion() != "HTTP/1.1")			//	Assuming that we accept only 1.1
	{
		setStatusCode(505);
		setStatusText("HTTP Version Not Supported");
	}
	else if (!fileExists())
	{
		setStatusCode(404);
		setStatusText("Not Found");
	}
	else if (!fileAccessible(request->getRequestURI()))
	{
		setStatusCode(403);
		setStatusText("Forbidden");
	}
	return (!getStatusCode());
}

void	Response::composeResponseMessage()
{
	responseMessage = getStatusLine();

	for (std::map<std::string, std::string>::iterator it = responseForm.begin(); it != responseForm.end(); ++it)
		responseMessage += it->first + ": " + it->second + "\r\n";

	responseMessage += "\n";						//	Empty line between headers and message body
	responseMessage += getMessageBody();
}

void	Response::respond(Request *request, Server *server, int clientSocket)
{
	setProtVersion(request->getProtVersion());

	if ((getStatusCode() != 0 && getStatusText() != "") || validateRequest(request) == false)
	{
			//	In case of an error
		setStatusLine(getProtVersion() + " " + std::to_string(getStatusCode()) + " " + getStatusText() + "\r\n");
		setMessageBody(std::to_string(getStatusCode()) + " " + getStatusText() + "\n");
	}
	else if (request->getMethod() == "GET")
	{
		setStatusCode(200);
		setStatusText("OK");
		setStatusLine(getProtVersion() + " " + std::to_string(getStatusCode()) + " " + getStatusText() + "\r\n");
		composeGetResponseBody();
	}
	else if (request->getMethod() == "POST")
	{
		setStatusCode(201);
		setStatusText("Created");
		setStatusLine(getProtVersion() + " " + std::to_string(getStatusCode()) + " " + getStatusText() + "\r\n");
		composeGetResponseBody();
		// composePostResponseBody();					//	For future use
	}
	responseHeaders(request, server);
	composeResponseMessage();						//	Compose whole response message from status line, headers and message body
	if (send(clientSocket, responseMessage.c_str(), responseMessage.size(), 0) == -1)
		error("Error while sending response message.");
}

void	Response::insertField(std::string const & key, std::string const & value)
{
	responseForm.insert(std::pair<std::string, std::string>(key, value));
}

void	Response::setProtVersion(std::string const & str)
{
	this->protVersion = str;
}

void	Response::setStatusCode(int c)
{
	this->statusCode = c;
}

void	Response::setStatusText(std::string const & str)
{
	this->statusText = str;
}

void	Response::setStatusLine(std::string const & str)
{
	this->statusLine = str;
}

void	Response::setMessageBody(std::string const & str)
{
	this->messageBody = str;
}

std::string	Response::getProtVersion() const
{
	return (this->protVersion);
}

int	Response::getStatusCode() const
{
	return (this->statusCode);
}

std::string	Response::getStatusText() const
{
	return (this->statusText);
}

std::string	Response::getStatusLine() const
{
	return (this->statusLine);
}

std::string	Response::getMessageBody() const
{
	return (this->messageBody);
}

void	Response::clear()
{
	this->statusCode = 0;
	this->protVersion.clear();
	this->statusText.clear();
	this->statusLine.clear();
	this->messageBody.clear();
	this->responseForm.clear();
	this->fullPath.clear();
	this->responseMessage.clear();
}
