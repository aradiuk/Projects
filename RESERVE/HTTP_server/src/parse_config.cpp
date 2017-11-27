#include "http.hpp"

void	parseError(std::string str, xmlDocPtr doc)
{
	std::cout << str << std::endl;
	if (doc)
		xmlFree(doc);
	exit(-1);
}

void	parseArguments(Server *server, xmlDocPtr doc, xmlNodePtr cur, xmlChar *temp, bool check[])
{
	int	port;
	int	threads;

	if (!xmlStrcmp(cur->name, (xmlChar *)"address"))	// <address> node
	{
		if (!temp)
			parseError("Address node is empty.", doc);

		server->setListenAddr((char *)temp);
		check[0] = true;
	}
	else if (!xmlStrcmp(cur->name, (xmlChar *)"path"))	// <path> node
	{
		if (!temp)
			parseError("Path node is empty.", doc);

		server->setRootDir((char *)temp);
		check[1] = true;
	}
	else if (!xmlStrcmp(cur->name, (xmlChar *)"port"))	// <port> node
	{
		if (!temp)					//	String is empty
			parseError("Port node is empty.", doc);
		if (!(port = atoi((char *)temp)))		//	String was alphabetical or equal 0
			parseError("Port is equal 0.", doc);
		if (port < 0)
			parseError("Port is negative.", doc);

		server->setPort(port);
		check[2] = true;
	}
	else if (!xmlStrcmp(cur->name, (xmlChar *)"threads"))	// <threads> node
	{
		if (!temp || !(threads = atoi((char *)temp)) || threads < 0)
			server->setNumOfThreads(server->defNumOfThreads);
		else
			server->setNumOfThreads(threads);
		check[3] = true;
	}
}

void	parseConfig(Server *server)
{
	xmlDocPtr	doc;
	xmlNodePtr	cur;
	xmlChar		*temp;
	std::string	str;
	bool		check[4] = {false};

	doc = xmlParseFile(server->confligFile.c_str());
	if (doc == NULL)
		parseError("Document wasn't parsed successfully.", 0);

	cur = xmlDocGetRootElement(doc);
	if (cur  == NULL)
		parseError("Document wasn't parsed successfully.", doc);

	if (xmlStrcmp(cur->name, (xmlChar *)"config"))
		parseError("Document of the wrong type.", doc);

	cur = cur->xmlChildrenNode;

	for (; cur != NULL; cur = cur->next)			//	Iterating through nodes passing them to parseArguments()
	{
		temp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		parseArguments(server, doc, cur, temp, check);
		xmlFree(temp);
	}
	for (int i = 0; i < 4; ++i)				//	Check if all arguments were parsed successfully
		if (!check[i])
			parseError("One or more tags are missing or wrong.", doc);
	xmlFree(doc);
	xmlFree(cur);
}
