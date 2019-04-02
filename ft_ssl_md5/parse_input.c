#include "ft_ssl_md5.h"

void ParseInput(int argc, char **argv, t_flags *flags)
{
    int i;

    i = 2;
    while (i < argc)
    {
        if (!ft_strcmp(argv[i], "-p"))
            InitFlag(print, "", flags);
        else if (!ft_strcmp(argv[i], "-q"))
            InitFlag(quiet, "", flags);
        else if (!ft_strcmp(argv[i], "-r"))
            InitFlag(reverse, "", flags);
        else if (!ft_strcmp(argv[i], "-s") && i + 1 < argc)
            InitFlag(string, argv[++i], flags);
        else
            InitFlag(file, argv[i], flags);
        ++i;
    }
}

void InitFlag(const t_flag_type flag_type, char *text, t_flags *flags)
{
    if (flags[flag_type].is_initialised) {
        errorFound("Same flag met more than once.\n");
    }

    flags[flag_type].is_initialised = 1;
    flags[flag_type].string_or_file = ft_strdup(text);
}

