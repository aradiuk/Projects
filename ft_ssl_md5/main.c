#include "ft_ssl.h"
#include <stdio.h>

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
    flags[print].add = 0;
    flags[quiet].add = 0;
    flags[reverse].add = 0;
    flags[string].add = ft_strnew(0);
    flags[file].add = ft_strnew(0);
    flags[print].flag_text = ft_strdup("-p");
    flags[quiet].flag_text = ft_strdup("-q");
    flags[reverse].flag_text = ft_strdup("-r");
    flags[string].flag_text = ft_strdup("-s");
    flags[file].flag_text = 0;
}

void clean_list(void *content, size_t size)
{
    size = 0;
    ft_strdel((char **)&content);
}

void clean_memory(t_flags *flags, t_list **invalid_args)
{
    int i;

    i = 0;
    while (i < MAX_FLAGS_IT)
    {
        if (flags[i].checksum)
            ft_strdel(&flags[i].checksum);
        if (flags[i].string_or_file)
            ft_strdel(&flags[i].string_or_file);
        if (flags[i].add)
            ft_strdel(&flags[i].add);
        if (flags[i].flag_text)
            ft_strdel(&flags[i].flag_text);
        ++i;
    }
    ft_lstdel(invalid_args, &clean_list);
}

int main(int argc, char **argv)
{
    t_flags flags[5];
    t_list  *invalid_args;

    invalid_args = 0;
    if (argc == 1)
    {
        ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
        return 1;
    }
    initial_flags(flags);
    parse_input(argc, argv, flags, &invalid_args);
    if (!ft_strcmp(argv[1], "md5"))
        try_md5(flags);
    else if (!ft_strcmp(argv[1], "sha256"))
        try_sha256(flags);
    else
    {
        error_found("ft_ssl: Error: an invalid command.\nMessage Digest commands:\n"
                  "md5\nsha256");
    }
    print_results(flags);
    ft_list_reverse(&invalid_args);
    ft_lstiter(invalid_args, &print_invalid_args);
    clean_memory(flags, &invalid_args);
    return 0;
}
