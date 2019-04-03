#include "ft_ssl.h"

void print_results(t_flags *flags)
{
    char    *file_add;
    char    *string_add;

    file_add = 0;
    string_add = 0;
    if (flags[print].is_initialised)
    {
        ft_putstr(flags[print].string_or_file);
        ft_putstr(flags[print].checksum);
        ft_putstr("\n");
    }
    else if (flags[print].string_or_file)
    {
        ft_putstr(flags[print].checksum);
        ft_putstr("\n");
    }
    prepare_file_and_string(flags, &file_add, &string_add);
    print_file_and_string(flags, file_add, string_add);
}

void prepare_file_and_string(t_flags *flags, char **file_add, char **string_add)
{
    char    *tmp;

    if (!flags[quiet].is_initialised)
    {
        if (!flags[reverse].is_initialised)
        {
            tmp = ft_strjoin("MD5 (", flags[file].string_or_file);
            *file_add = ft_strjoin(tmp, ") = \0");
            ft_strdel(&tmp);
            tmp = ft_strjoin("MD5 (\"", flags[string].string_or_file);
            *string_add = ft_strjoin(tmp, "\") = \0");
            ft_strdel(&tmp);
        }
        else
        {
            tmp = ft_strjoin(" ", flags[file].string_or_file);
            *file_add = ft_strjoin(tmp, "\0");
            ft_strdel(&tmp);
            tmp = ft_strjoin(" \"", flags[string].string_or_file);
            *string_add = ft_strjoin(tmp, "\"\0");
            ft_strdel(&tmp);
        }
    }
}

void print_file_and_string(t_flags *flags, char *file_add, char *string_add)
{
    if (!flags[reverse].is_initialised)
    {
        ft_putstr(string_add);
        ft_putstr(flags[string].checksum);
        if (flags[string].checksum)
            ft_putstr("\n");
        ft_putstr(file_add);
        ft_putstr(flags[file].checksum);
        if (flags[file].checksum)
            ft_putstr("\n");
    }
    else
    {
        ft_putstr(flags[string].checksum);
        ft_putstr(string_add);
        if (flags[string].checksum)
            ft_putstr("\n");
        ft_putstr(flags[file].checksum);
        ft_putstr(file_add);
        if (flags[file].checksum)
            ft_putstr("\n");
    }
}

