#include "ft_ssl.h"

void ft_ssl_md5_checksum(const char *str, t_flags *flag)
{
    t_ssl_md5_ctx context;
    t_byte digest[16];

    ft_strcpy(flag->string_or_file, str);
    ft_ssl_md5_init(&context);
    ft_ssl_md5_update(&context, (unsigned char *)str, ft_strlen(str));
    ft_ssl_md5_final(digest, &context);

    flag->checksum = ft_strnew(32);
    ft_ssl_md5_make_string(digest, flag->checksum);
}

void ft_ssl_sha256_checksum(const char *str, t_flags *flag)
{

}

void try_md5(t_flags *flags)
{
    int fd;

    if (flags[file].is_initialised)
    {
        fd = open(flags[file].string_or_file, O_RDONLY);
        if (fd == -1)
        {
            error_found("Can't open a file.");
        }
        ft_ssl_md5_checksum(read_data(fd), &flags[file]);
        close(fd);
    }
    if (flags[string].is_initialised)
        ft_ssl_md5_checksum(flags[string].string_or_file, &flags[string]);
    if (flags[print].is_initialised || !flags[file].is_initialised)
    {
        flags[print].string_or_file = read_data(0);
        ft_ssl_md5_checksum(flags[print].string_or_file, &flags[print]);
    }
}

void try_sha256(t_flags *flags)
{
    int fd;

    if (flags[file].is_initialised)
    {
        fd = open(flags[file].string_or_file, O_RDONLY);
        if (fd == -1)
        {
            error_found("Can't open a file.");
        }
        ft_ssl_sha256_checksum(read_data(fd), &flags[file]);
        close(fd);
    }
    if (flags[string].is_initialised)
        ft_ssl_sha256_checksum(flags[string].string_or_file, &flags[string]);
    if (flags[print].is_initialised || !flags[file].is_initialised)
    {
        flags[print].string_or_file = read_data(0);
        ft_ssl_sha256_checksum(flags[print].string_or_file, &flags[print]);
    }
}

char* read_data(int fd)
{
    char    *tmp;
    char    *file;
    char    *gnl;

    file = ft_strnew(0);
    while (get_next_line(fd, &gnl) > 0)
    {
        tmp = ft_strjoin(file, gnl);
        free(file);
        free(gnl);
        file = ft_strjoin(tmp, "\n");
        free(tmp);
    }
    return file;
}
