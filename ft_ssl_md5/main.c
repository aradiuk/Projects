#include "ft_ssl_md5.h"

void errorFound(char *errorText)
{
    ft_putstr(errorText);
    exit(1);
}

void InitialFlags(t_flags *flags)
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
}

int main(int argc, char **argv)
{
    t_flags flags[5];
    InitialFlags(flags);

    if (argc == 1)
    {
        ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
        return 1;
    }
    ParseInput(argc, argv, flags);
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

    return 0;
}
