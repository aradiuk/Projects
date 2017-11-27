#ifndef STD_H
# define STD_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <libxml/xmlmemory.h>
# include <libxml/parser.h>
# include <unistd.h>
# include <curl/curl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pthread.h>
# include <errno.h>
typedef struct	s_info
{
	pthread_mutex_t mutex;
	int	default_threads;
	int	downloads;
	int	number_of_urls;
	int	number_of_threads;
	int	path_length;
	xmlChar	*user_agent;
	xmlChar	**urls;
	xmlChar	*path;
}		t_info;

typedef	struct	s_thread
{
	t_info	*info;
	int	url_number;
	int	thread_num;
}		t_thread;

# define DEFAULT_UA "My User Agent"

void	parse_file(char *filename, t_info *info);
void	error(char *str, xmlDocPtr doc);
void	read_urls(xmlDocPtr doc, xmlNodePtr cur, t_info *info);
void	read_conf_params(xmlDocPtr doc, xmlNodePtr cur, t_info *info);
xmlChar	*read_path(xmlDocPtr doc, xmlNodePtr cur);
void	*download_file(void *data);
void	create_directory(xmlChar *path);
void	pthreading_download(t_info *info);
char	*filepath_derive(t_info *info, int url_counter, int path_length);
t_thread	*data_for_thread(t_info *info, int thread_number);

#endif // STD_H
