#include "ft_ssl.h"

void parse_input(int argc, char **argv, t_flags *flags)
{
    int i;

    i = 2;
    while (i < argc)
    {
        if (!ft_strcmp(argv[i], "-p"))
            init_flag(print, "", flags);
        else if (!ft_strcmp(argv[i], "-q"))
            init_flag(quiet, "", flags);
        else if (!ft_strcmp(argv[i], "-r"))
            init_flag(reverse, "", flags);
        else if (!ft_strcmp(argv[i], "-s") && i + 1 < argc)
            init_flag(string, argv[++i], flags);
        else
            init_flag(file, argv[i], flags);
        ++i;
    }
}

void init_flag(const t_flag_type flag_type, char *text, t_flags *flags)
{
    if (flags[flag_type].is_initialised) {
        error_found("Same flag met more than once.\n");
    }

    flags[flag_type].is_initialised = 1;
    flags[flag_type].string_or_file = ft_strdup(text);
}

