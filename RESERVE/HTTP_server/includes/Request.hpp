#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "http.hpp"
#include <map>

class	Request
{
private:
	std::string	method;
	std::string	requestURI;
	std::string	protVersion;
	std::string	messageBody;
	std::map<std::string, std::string> requestForm;

public:
	Request();
	void		setMethod(std::string const & str);
	void		setRequestURI(std::string const & str);
	void		setProtVersion(std::string const & str);
	void		setMessageBody(std::string const & str);
	std::string	getMethod() const;
	std::string	getRequestURI() const;
	std::string	getProtVersion() const;
	std::string	getMessageBody() const;
	std::string	getHeaderValue(std::string const & str) const;
	std::string	getExtension(std::string const & str) const;

	void		insertField(std::string const & str);
	void		clear();
};

#endif	//	REQUEST_HPP
