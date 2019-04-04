#include "ft_ssl.h"

void parse_input(int argc, char **argv, t_flags *flags, t_list **invalid_args)
{
    int i;

    i = 2;
    while (i < argc)
    {
        if (!ft_strcmp(argv[i], "-p"))
            init_flag(print, "", flags, invalid_args);
        else if (!ft_strcmp(argv[i], "-q"))
            init_flag(quiet, "", flags, invalid_args);
        else if (!ft_strcmp(argv[i], "-r"))
            init_flag(reverse, "", flags, invalid_args);
        else if (!ft_strcmp(argv[i], "-s") && i + 1 < argc)
            init_flag(string, argv[++i], flags, invalid_args);
        else
            init_flag(file, argv[i], flags, invalid_args);
        ++i;
    }
}

void init_flag(const t_flag_type flag_type, char *text, t_flags *flags, t_list **invalid_args)
{
    char *tmp;

    if (flags[flag_type].is_initialised) {
        if (flags[flag_type].flag_text)
        {
            tmp = ft_strjoin(flags[flag_type].flag_text, ": No such file or directory\n\0");
            ft_lstadd(invalid_args, ft_lstnew((void *)tmp, ft_strlen(tmp)));
            ft_strdel(&tmp);
        }
        if (ft_strcmp(text, ""))
        {
            tmp = ft_strjoin(text, ": No such file or directory\n\0");
            ft_lstadd(invalid_args, ft_lstnew((void *)tmp, ft_strlen(tmp)));
            ft_strdel(&tmp);
        }
        return;
    }

    flags[flag_type].is_initialised = 1;
    flags[flag_type].string_or_file = ft_strdup(text);
}

