#ifndef __FT_SSL_MD5__
#define __FT_SSL_MD5__


#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define MAX_FLAGS_IT 5

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

void errorFound(char *errorText);
void InitialFlags(t_flags *flags);

void ParseInput(int argc, char **argv, t_flags *flags);
void InitFlag(t_flag_type flagType, char *text, t_flags *flags);


void try_md5(t_flags *flags);
void try_sha256(t_flags *flags);
char* read_data(int fd);


char* md5_checksum(const char *str);

char* sha256_checksum(const char *str);

#endif
