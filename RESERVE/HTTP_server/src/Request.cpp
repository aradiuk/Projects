#include "http.hpp"

Request::Request() : method(""), requestURI(""), protVersion(""),
		messageBody("")
{}

void	Request::setMethod(std::string const & str)
{
	this->method = str;
}

void	Request::setRequestURI(std::string const & str)
{
	this->requestURI = str;
}

void	Request::setProtVersion(std::string const & str)
{
	this->protVersion = str;
}

void	Request::setMessageBody(std::string const & str)
{
	this->messageBody = str;
}

std::string	Request::getMethod() const
{
	return (this->method);
}

std::string	Request::getRequestURI() const
{
	return (this->requestURI);
}

std::string	Request::getProtVersion() const
{
	return (this->protVersion);
}

std::string	Request::getMessageBody() const
{
	return (this->messageBody);
}

std::string	Request::getHeaderValue(std::string const & str) const
{
	std::map<std::string, std::string>::const_iterator it;

	it = requestForm.find(str);
	if (it != requestForm.end())
		return (it->second);
	else
		return ("");
}

std::string	Request::getExtension(std::string const & str) const
{
	size_t		pos;
	std::string	res;

	pos = str.rfind('.', std::string::npos);	//	Find last occurance of '.' in a string
	if (pos != std::string::npos)
		return (str.substr(pos + 1));
	else
		return ("");
}

void	Request::insertField(std::string const & str)
{
	std::string	header;
	std::string	value;
	size_t		spaceColonPos;

	spaceColonPos = str.find(": ");
	if (spaceColonPos == std::string::npos)
		return;

	header = str.substr(0, spaceColonPos);		//	substr string before ": "
	value = str.substr(spaceColonPos + 2);		//	+2 because of ": " between field and value
	requestForm.insert(std::pair<std::string, std::string>(header, value));
}

void	Request::clear()
{
	this->method.clear();
	this->requestURI.clear();
	this->protVersion.clear();
	this->messageBody.clear();
	this->requestForm.clear();
}
