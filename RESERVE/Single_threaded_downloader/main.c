#include "std.h"

void	error(char *str, xmlDocPtr doc)
{
	printf("%s\n", str);
	if (doc != 0)
		xmlFreeDoc(doc);
	exit(0);
}

void	read_conf_params(xmlDocPtr doc, xmlNodePtr cur, t_info *info)
{
	xmlNodePtr	node;
	xmlChar	*threads_check;

	threads_check = 0;
	info->number_of_threads = 0;
	info->user_agent = 0;
	node = cur;
	while (xmlStrcmp(node->name, (xmlChar *)"section1") && node->next)
		node = node->next;
	if (xmlStrcmp(node->name, (xmlChar *)"section1"))
		error("Wrong first section tag.", doc);
	node = node->xmlChildrenNode;

	//	Iterating through nodes in the current section looking for <user-agent> element
	for (; node != NULL; node = node->next)
	{
		if ((!xmlStrcmp(node->name, (xmlChar *)"user-agent")))
		{
			if (!(info->user_agent = xmlNodeListGetString(doc, node->xmlChildrenNode, 1)))
				info->user_agent = (xmlChar *)strdup(DEFAULT_UA);
			}
		else if ((!xmlStrcmp(node->name, (xmlChar *)"threads")))
		{
			if (!(threads_check = xmlNodeListGetString(doc, node->xmlChildrenNode, 1)))
				info->number_of_threads = DEFAULT_THREADS;
			else if (!(info->number_of_threads = atoi((char *)threads_check)))
				info->number_of_threads = DEFAULT_THREADS;
		}
	}
}

void	read_urls(xmlDocPtr doc, xmlNodePtr cur, t_info *info)
{
	xmlNodePtr	node;
	int		i = 0;
	int		url_length;

	info->number_of_urls = 0;
	node = cur;

		//	Placing node pointer to appropriate element
	while (xmlStrcmp(node->name, (xmlChar *)"section2") && node->next)
		node = node->next;
	if (xmlStrcmp(node->name, (xmlChar *)"section2"))
		error("Wrong second section tag.", doc);
	node = node->xmlChildrenNode;

		//	Iterating through nodes counting total number of URLs used
	for (xmlNodePtr	pass = node; pass != NULL; pass = pass->next)
	{
		if ((!xmlStrcmp(pass->name, (xmlChar *)"url")))
			info->number_of_urls++;
	}

	if (info->number_of_urls == 0)
		error("URL element content is empty.", doc);

	info->urls = (xmlChar **)malloc(sizeof(xmlChar *) * info->number_of_urls + 1);
		//	Iterating through nodes in the current section looking for
		//			<url> elementand filling in the array
	for (; node != NULL; node = node->next)
	{
		if ((!xmlStrcmp(node->name, (xmlChar *)"url")))
		{
			if (!(info->urls[i++] = xmlNodeListGetString(doc, node->xmlChildrenNode, 1)))
				error("URL element content is empty.", doc);
			else	//	Removing last slash symbol
			{
				url_length = strlen((char *)info->urls[i - 1]);
				if (((char *)info->urls[i - 1])[url_length - 1] == '/')
					info->urls[i - 1][url_length - 1] = 0;
			}
		}
	}
	info->urls[i] = 0;
}

xmlChar	*read_path(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlNodePtr	node;

	node = cur;

		//	Placing node pointer to appropriate element
	while (xmlStrcmp(node->name, (xmlChar *)"section3") && node->next)
		node = node->next;
	if (xmlStrcmp(node->name, (xmlChar *)"section3"))
		error("Wrong third section tag.", doc);
	node = node->xmlChildrenNode;

		//	Iterating through nodes in the current section looking for <path> element
	for (; node != NULL; node = node->next)
	{
		if ((!xmlStrcmp(node->name, (xmlChar *)"path")))
			return (xmlNodeListGetString(doc, node->xmlChildrenNode, 1));
	}
	return (0);
}

void	parse_file(char *filename, t_info *info)
{
	xmlDocPtr	doc;
	xmlNodePtr	cur;

	doc = xmlParseFile(filename);

	if (doc == NULL)
		error("Document wasn't parsed successfully.", 0);
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
		error("Document wasn't parsed successfully.", doc);
	if (xmlStrcmp(cur->name, (xmlChar *)"config"))
		error("Document of the wrong type.", doc);

	cur = cur->xmlChildrenNode;

		//	Parsing first section
	read_conf_params(doc, cur, info);

		//	Parsing second section
	read_urls(doc, cur, info);

		//	Parsing third section
	info->path = 0;
	if (!(info->path = read_path(doc, cur)))
		error("Path element content is empty.", doc);
	info->path_length = strlen((char *)info->path);
}

int main(int argc, char **argv)
{
	t_info	*info;
	int	fd;

	if (argc != 2)
		error("Usage: ./std config_file", 0);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("Couldn't open config file.", 0);
	close(fd);

	info = (t_info *)malloc(sizeof(t_info));
	pthread_mutex_init(&info->mutex, NULL);
	parse_file(argv[1], info);
	if (info->number_of_threads > info->number_of_urls)
		info->number_of_threads = info->number_of_urls;
	pthreading_download(info);

	printf("\nAFTER THREADS\n");
		//	Freeing the memory used for saving info
	pthread_mutex_destroy(&info->mutex);
	xmlFree(info->user_agent);
	xmlFree(info->path);
	for (int i = 0; i < info->number_of_urls; i++)
		xmlFree(info->urls[i]);
	free(info->urls);
	free(info);
	return (0);
}
