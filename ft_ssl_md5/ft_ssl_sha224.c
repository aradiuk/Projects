#include "ft_ssl.h"

void ft_ssl_sha224_checksum(const char *str, t_flags *flag)
{
    t_ssl_sha256_ctx    context;
    t_byte              digest[28];

    ft_ssl_sha224_init(&context);
    ft_ssl_sha224_update(&context, (unsigned char *)str, ft_strlen(str));
    ft_ssl_sha224_final(digest, &context);
    flag->checksum = ft_strnew(56);
    ft_ssl_md5_make_string(digest, flag->checksum, 28);
}

void ft_ssl_sha224_init(t_ssl_sha256_ctx *context)
{
    context->st[0] = 0xc1059ed8;
    context->st[1] = 0x367cd507;
    context->st[2] = 0x3070dd17;
    context->st[3] = 0xf70e5939;
    context->st[4] = 0xffc00b31;
    context->st[5] = 0x68581511;
    context->st[6] = 0x64f98fa7;
    context->st[7] = 0xbefa4fa4;
    context->num_of_bits[0] = 0;
    context->num_of_bits[1] = 0;
}

void ft_ssl_sha224_update(t_ssl_sha256_ctx *context, t_byte *str, unsigned int str_len)
{
    ft_ssl_sha256_update(context, str, str_len);
}

void ft_ssl_sha224_final(t_byte digest[32], t_ssl_sha256_ctx *context)
{
    ft_ssl_sha256_final(digest, context);
}

