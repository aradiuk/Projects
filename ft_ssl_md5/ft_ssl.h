#ifndef __FT_SSL_MD5__
#define __FT_SSL_MD5__

# include "ft_ssl_md5.h"

# define MAX_FLAGS_IT 5

typedef enum    e_flag_type
{
    print,
    quiet,
    reverse,
    string,
    file
}               t_flag_type;

typedef struct  s_flags
{
    int is_initialised;
    char *string_or_file;
    char *checksum;
}               t_flags;

void error_found(char *errorText);
void initial_flags(t_flags *flags);
void print_results(t_flags *flags);

void parse_input(int argc, char **argv, t_flags *flags);
void init_flag(t_flag_type flagType, char *text, t_flags *flags);


void try_md5(t_flags *flags);
void try_sha256(t_flags *flags);
char* read_data(int fd);


void ft_ssl_md5_checksum(const char *str, t_flags *flag);
void ft_ssl_sha256_checksum(const char *str, t_flags *flag);

#endif
