#include "ft_ssl.h"

void error_found(char *errorText)
{
    ft_putstr(errorText);
    ft_putstr("\n");
    exit(1);
}

void initial_flags(t_flags *flags)
{
    flags[print].is_initialised = 0;
    flags[quiet].is_initialised = 0;
    flags[reverse].is_initialised = 0;
    flags[string].is_initialised = 0;
    flags[file].is_initialised = 0;
    flags[print].string_or_file = 0;
    flags[quiet].string_or_file = 0;
    flags[reverse].string_or_file = 0;
    flags[string].string_or_file = 0;
    flags[file].string_or_file = 0;
    flags[print].checksum = 0;
    flags[quiet].checksum = 0;
    flags[reverse].checksum = 0;
    flags[string].checksum = 0;
    flags[file].checksum = 0;
}

void clean_memory(t_flags *flags)
{
    int i;

    i = 0;
    while (i < MAX_FLAGS_IT)
    {
        if (flags[i].checksum)
            ft_strdel(&flags[i].checksum);
        if (flags[i].string_or_file)
            ft_strdel(&flags[i].string_or_file);
        ++i;
    }
}

int main(int argc, char **argv)
{
    t_flags flags[5];

    initial_flags(flags);
    if (argc == 1)
    {
        ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
        return 1;
    }
    parse_input(argc, argv, flags);
    if (!ft_strcmp(argv[1], "md5"))
        try_md5(flags);
    else if (!ft_strcmp(argv[1], "sha256"))
        try_sha256(flags);
    else
    {
        ft_putstr("ft_ssl: Error: an invalid command.\n"
                  "Message Digest commands:\n"
                  "md5\n"
                  "sha256\n");
        return 1;
    }
    print_results(flags);
    clean_memory(flags);
    return 0;
}
