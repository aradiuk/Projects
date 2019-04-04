#include "ft_ssl.h"

void ft_ssl_md5_checksum(const char *str, t_flags *flag)
{
    t_ssl_md5_ctx   context;
    t_byte          digest[16];

    ft_ssl_md5_init(&context);
    ft_ssl_md5_update(&context, (unsigned char *)str, ft_strlen(str));
    ft_ssl_md5_final(digest, &context);
    flag->checksum = ft_strnew(32);
    ft_ssl_md5_make_string(digest, flag->checksum, 16);
}

void ft_ssl_sha256_checksum(const char *str, t_flags *flag)
{
    t_ssl_sha256_ctx    context;
    t_byte              digest[32];

    ft_ssl_sha256_init(&context);
    ft_ssl_sha256_update(&context, (unsigned char *)str, ft_strlen(str));
    ft_ssl_sha256_final(digest, &context);
    flag->checksum = ft_strnew(64);
    ft_ssl_md5_make_string(digest, flag->checksum, 32);
}

void try_md5(t_flags *flags)
{
    int fd;
    char *input;

    flags[file].add = ft_strdup("MD5 (");
    flags[string].add = ft_strdup("MD5 (\"");
    if (flags[file].is_initialised)
    {
        fd = open(flags[file].string_or_file, O_RDONLY);
        if (fd == -1)
        {
            error_found("Can't open a file.");
        }
        input = read_data(fd);
        ft_ssl_md5_checksum(input, &flags[file]);
        close(fd);
        ft_strdel(&input);
    }
    if (flags[string].is_initialised)
        ft_ssl_md5_checksum(flags[string].string_or_file, &flags[string]);
    if (flags[print].is_initialised || (!flags[file].is_initialised && !flags[string].is_initialised))
    {
        flags[print].string_or_file = read_data(0);
        ft_ssl_md5_checksum(flags[print].string_or_file, &flags[print]);
    }
}

void try_sha256(t_flags *flags)
{
    int fd;
    char *input;

    flags[file].add = ft_strdup("SHA256 (");
    flags[string].add = ft_strdup("SHA256 (\"");
    if (flags[file].is_initialised)
    {
        fd = open(flags[file].string_or_file, O_RDONLY);
        if (fd == -1)
        {
            error_found("Can't open a file.");
        }
        input = read_data(fd);
        ft_ssl_sha256_checksum(input, &flags[file]);
        close(fd);
        ft_strdel(&input);
    }
    if (flags[string].is_initialised)
        ft_ssl_sha256_checksum(flags[string].string_or_file, &flags[string]);
    if (flags[print].is_initialised || (!flags[file].is_initialised && !flags[string].is_initialised))
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
        ft_strdel(&file);
        ft_strdel(&gnl);
        file = ft_strjoin(tmp, "\n");
        ft_strdel(&tmp);
    }
    return file;
}
