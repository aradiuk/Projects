#include "std.h"

struct stat st = {0};

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t	written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return (written);
}

void	create_directory(xmlChar *path_xml)
{
	char	*path;
	char	*temp;
	int	length;

	path = (char *)path_xml;
	length = strlen(path);
	if (path[length - 1] == '/')
		path[length - 1] = 0;
	temp = (path + 1);

		// Recursively creating directories
	while (*temp)
	{
		if (*temp == '/')
		{
			*temp = 0;
			if (stat(path, &st) == -1)
				if (mkdir(path, 0777) == -1)
					error("Couldn't create a directory.", 0);
			*temp = '/';
		}
		temp++;
	}
	if (mkdir(path, 0777) == -1)
		error("Couldn't create a directory.", 0);
}
char	*filepath_derive(t_info *info, int url_num, int path_length)
{
	char	*filename;
	char	*filepath;
	int	name_length;

		//	Creating filename by concatenating path and the last part of URL
		//					(or the whole URL in some cases)
	filename = strrchr((char *)info->urls[url_num], '/');				// Points to the last slash in URL
	name_length = filename ? strlen(filename) : strlen((char *)info->urls[url_num]);	// Determining length of the filename depending on URL
	filepath = (char *)malloc(path_length + name_length + 1);
	filepath = strncpy(filepath, (char *)info->path, path_length + 1);
	if (filename)
		filepath = strncat(filepath, filename, name_length);
	else
		filepath = strncat(strcat(filepath, "/"), (char *)info->urls[url_num], name_length);
	return (filepath);
}

void	*download_file(void* data_voided)
{
	CURLcode	res;
	CURL		*easyhandle;
	FILE*		file;
	char		*filepath;
	t_info		*info = ((t_thread *)data_voided)->info;
	t_thread	*data = (t_thread *)data_voided;

	easyhandle = curl_easy_init();
	if (!easyhandle)
		error("Failed to create easyhandle.", 0);

	if (pthread_mutex_lock(&info->mutex))
		error("Mutex lock failed", 0);
	++info->downloads;
	if (pthread_mutex_unlock(&info->mutex))
		error("Mutex unlock failed", 0);

		//	Itering through all URLs and downloading them
	curl_easy_reset(easyhandle);
	curl_easy_setopt(easyhandle, CURLOPT_URL, info->urls[data->url_number]);

		//	Checking if directory exists and creating it in case it doesn't
	if (stat((char *)info->path, &st) == -1)
		create_directory(info->path);

	printf("Thread number '%d' is downloading url number '%d', which is %s\n", data->thread_num, data->url_number, info->urls[data->url_number]);
	filepath = filepath_derive(info, data->url_number, info->path_length);
	file = fopen(filepath, "w");
	if (!file)
		error("Couldn't open a file.", 0);

	curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file);
	res = curl_easy_perform(easyhandle);
	if (res != CURLE_OK)
	{
		if (remove(filepath))
			printf("Couldn't remove the file %s\n", filepath);
		printf("Download of the '%s' failed.\n", info->urls[data->url_number]);
	}

	fclose(file);
	free(filepath);
	curl_easy_cleanup(easyhandle);

		// Routine for giving threads new tasks
	pthread_mutex_lock(&info->mutex);
	if (info->downloads < info->number_of_urls)
	{
		data->url_number = info->downloads;
		pthread_mutex_unlock(&info->mutex);
		download_file(data_voided);
	}
	else
		pthread_mutex_unlock(&info->mutex);
	free(data_voided);
	printf("Thread number %d is terminating.\n", data->thread_num);
	pthread_exit(data_voided);
}

void pthreading_download(t_info *info)
{
	pthread_t	threads[info->number_of_threads];
	pthread_attr_t	attr;
	t_thread	*data;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	info->downloads = 0;
	for (int i = 0; i < info->number_of_threads; i++)
	{
		data = data_for_thread(info, i);
		if (pthread_create(&threads[i], &attr, download_file, (void *)data))
			error("Couldn't create a thread.", 0);
	}
	pthread_attr_destroy(&attr);
	for (int i = 0; i < info->number_of_threads; i++)
		pthread_join(threads[i], NULL);
}

t_thread	*data_for_thread(t_info *info, int thread_number)
{
	t_thread	*data;

	data = (t_thread *)malloc(sizeof(t_thread));
	data->info = info;
	data->thread_num = thread_number;
	data->url_number = thread_number;
}

// void	download_file(t_info *info)
// {
// 	CURLcode	res;
// 	CURL		*easyhandle;
// 	FILE*		file;
// 	char		*filepath;
// 	int		url_counter = 0;
// 	int		path_length;
//
// 	easyhandle = curl_easy_init();
// 	if (!easyhandle)
// 		return ;
//
// 		//	Itering through all URLs and downloading them
// 	path_length = strlen((char *)info->path);
// 	while (url_counter < info->number_of_urls)
// 	{
// 		curl_easy_reset(easyhandle);
// 		curl_easy_setopt(easyhandle, CURLOPT_URL, info->urls[url_counter]);
//
// 			//	Checking if directory exists and creating it in case it doesn't
// 		if (stat((char *)info->path, &st) == -1)
// 			create_directory(info->path);
//
// 		filepath = filepath_derive(info, url_counter, path_length);
// 		file = fopen(filepath, "w");
// 		if (!file)
// 			error("Couldn't open a file.", 0);
//
// 		curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data);
// 		curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file);
// 		res = curl_easy_perform(easyhandle);
// 		if (res != CURLE_OK)
// 			{
// 				if (remove(filepath))
// 					printf("Couldn't remove the file %s\n", filepath);
// 				printf("Download of the '%s' failed.\n", info->urls[url_counter]);
// 			}
//
// 		fclose(file);
// 		free(filepath);
// 		++url_counter;
// 	}
// 	curl_easy_cleanup(easyhandle);
// }
