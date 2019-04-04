#include "ft_ssl_sha256.h"

void ft_ssl_sha256_decode(uint32_t *out, t_byte *in, unsigned int in_len)
{
    unsigned int i;
    unsigned int j;

    i = 0;
    j = 0;
    while (j < in_len)
    {
        out[i] = (((uint32_t)in[j]) << 24) |
                    (((uint32_t)in[++j]) << 16) |
                    (((uint32_t)in[++j]) << 8) |
                    ((uint32_t)in[++j]);

        ++i;
        ++j;
    }
}

void ft_ssl_sha256_encode(t_byte *out, uint32_t *in, unsigned int in_len)
{
    unsigned int i;
    unsigned int j;

    i = 0;
    j = 0;
    while (j < in_len)
    {
        out[j] = (t_byte)((in[i] >> 24) & 0xff);
        out[++j] = (t_byte)((in[i] >> 16) & 0xff);
        out[++j] = (t_byte)((in[i] >> 8) & 0xff);
        out[++j] = (t_byte)(in[i] & 0xff);
        ++i;
        ++j;
    }
}

void ft_ssl_sha256_encode_num_of_bits(t_byte *out, uint32_t *in, unsigned int in_len)
{
    unsigned int i;
    unsigned int j;

    i = 1;
    j = 0;
    while (j < in_len)
    {
        out[j] = (t_byte)((in[i] >> 24) & 0xff);
        out[++j] = (t_byte)((in[i] >> 16) & 0xff);
        out[++j] = (t_byte)((in[i] >> 8) & 0xff);
        out[++j] = (t_byte)(in[i] & 0xff);
        --i;
        ++j;
    }
}

void ft_ssl_sha256_make_string(unsigned char digest[16], char *result)
{
    unsigned int i;
    unsigned int j;
    unsigned int tmp;

    i = 0;
    j = 0;
    while (i < 16)
    {
        tmp = digest[i] / 16;
        if (tmp >= 10)
            result[j] = 'a' + tmp - 10;
        else
            result[j] = '0' + tmp;
        tmp = digest[i] % 16;
        if (tmp >= 10)
            result[++j] = 'a' + tmp - 10;
        else
            result[++j] = '0' + tmp;
        ++i;
        ++j;
    }
    result[j] = 0;
}
