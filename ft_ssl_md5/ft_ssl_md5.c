#include "ft_ssl_md5.h"

static unsigned char g_padding[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void ft_ssl_md5_init(t_ssl_md5_ctx *context)
{
    context->st[0] = 0x67452301;
    context->st[1] = 0xefcdab89;
    context->st[2] = 0x98badcfe;
    context->st[3] = 0x10325476;
    context->num_of_bits[0] = 0;
    context->num_of_bits[1] = 0;
}

void ft_ssl_md5_update(t_ssl_md5_ctx *context, t_byte *str, unsigned int str_len)
{
    unsigned int i;
    unsigned int curr_index;
    unsigned int part_length;

    curr_index = (unsigned int)((context->num_of_bits[0] >> 3) & 63);
    if ((context->num_of_bits[0] += ((uint32_t)str_len << 3)) < ((uint32_t)str_len << 3))
        context->num_of_bits[1]++;
    context->num_of_bits[1] += ((uint32_t)str_len >> 29);
    part_length = FT_MD5_BUFFER_SIZE - curr_index;
    if (str_len >= part_length)
    {
        ft_memcpy(&context->buffer[curr_index], str, part_length);
        ft_ssl_md5_transform(context->st, context->buffer);
        i = part_length;
        while (i + 63 < str_len)
        {
            ft_ssl_md5_transform(context->st, &str[i]);
            i += FT_MD5_BUFFER_SIZE;
        }
        curr_index = 0;
    }
    else
    {
        i = 0;
    }
    ft_memcpy(&context->buffer[curr_index], &str[i], str_len - i);
}

void ft_ssl_md5_final(t_byte digest[16], t_ssl_md5_ctx *context)
{
    t_byte          bits[8];
    unsigned int    curr_index;
    unsigned int    pad_length;

    ft_ssl_md5_encode(bits, context->num_of_bits, 8);
    curr_index = (unsigned int)((context->num_of_bits[0] >> 3) & 63);
    pad_length = (curr_index < 56) ? (56 - curr_index) : (120 - curr_index);
    ft_ssl_md5_update(context, g_padding, pad_length);
    ft_ssl_md5_update(context, bits, 8);
    ft_ssl_md5_encode(digest, context->st, 16);
    ft_bzero(context, sizeof(t_ssl_md5_ctx));
}

