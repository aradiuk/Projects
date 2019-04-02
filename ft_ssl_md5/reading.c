#include "ft_ssl_md5.h"

void try_md5(t_flags *flags)
{
    int fd;

    if (flags[file].is_initialised)
    {
        fd = open(flags[file].string_or_file, O_RDONLY);
        flags[file].checksum = ft_strdup(md5_checksum(read_data(fd)));
        close(fd);
    }
    if (flags[string].is_initialised)
        flags[string].checksum = ft_strdup(md5_checksum(flags[string].string_or_file));
    if (flags[print].is_initialised || !flags[file].is_initialised)
        flags[file].checksum = ft_strdup(md5_checksum(read_data(0)));
}

void try_sha256(t_flags *flags)
{
    int fd;

    if (flags[file].is_initialised)
    {
        fd = open(flags[file].string_or_file, O_RDONLY);
        flags[file].checksum = ft_strdup(sha256_checksum(read_data(fd)));
        close(fd);
    }
    if (flags[string].is_initialised)
        flags[string].checksum = ft_strdup(sha256_checksum(flags[string].string_or_file));
    if (flags[print].is_initialised || !flags[file].is_initialised)
        flags[file].checksum = ft_strdup(sha256_checksum(read_data(0)));
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
    printf("%s\n", file);
    return file;
}
