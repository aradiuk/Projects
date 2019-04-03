#include "ft_ssl.h"

void error_found(char *errorText)
{
    ft_putstr(errorText);
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

void print_results(t_flags *flags)
{
    if (flags[print].is_initialised)
    {
        ft_putstr(flags[print].string_or_file);
        ft_putstr(flags[print].checksum);
        ft_putstr("\n");
    }
    if (flags[string].is_initialised)
    {
        ft_putstr(flags[string].string_or_file);
        ft_putstr(flags[string].checksum);
        ft_putstr("\n");
    }
    if (flags[file].is_initialised)
    {
        ft_putstr(flags[file].string_or_file);
        ft_putstr(flags[file].checksum);
        ft_putstr("\n");
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
    {
        try_md5(flags);
        print_results(flags);
    }
    else if (!ft_strcmp(argv[1], "sha256"))
    {
        try_sha256(flags);
        print_results(flags);
    }
    else
    {
        ft_putstr("ft_ssl: Error: an invalid command.\n"
                  "Message Digest commands:\n"
                  "md5\n"
                  "sha256\n");
        return 1;
    }

    return 0;
}
