#ifndef __FT_SSL_MD5_H__
#define __FT_SSL_MD5_H__

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

# define FT_MD5_BUFFER_SIZE 64

# define S11 7
# define S12 12
# define S13 17
# define S14 22
# define S21 5
# define S22 9
# define S23 14
# define S24 20
# define S31 4
# define S32 11
# define S33 16
# define S34 23
# define S41 6
# define S42 10
# define S43 15
# define S44 21

# define F(a, b, c) (((a) & (b)) | ((~a) & (c)))
# define G(a, b, c) (((a) & (c)) | ((b) & (~c)))
# define H(a, b, c) ((a) ^ (b) ^ (c))
# define I(a, b, c) ((b) ^ ((a) | (~c)))
# define ROT_L(a, n) (((a) << (n)) | ((a) >> (32-(n))))
# define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac); \
 (a) = ROT_L ((a), (s)); \
 (a) += (b); \
  }
# define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac); \
 (a) = ROT_L ((a), (s)); \
 (a) += (b); \
  }
# define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac); \
 (a) = ROT_L ((a), (s)); \
 (a) += (b); \
  }
# define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac); \
 (a) = ROT_L ((a), (s)); \
 (a) += (b); \
  }
typedef unsigned char t_byte;

typedef struct  s_ssl_md5_context
{
    uint32_t    st[4];
    t_byte      buffer[FT_MD5_BUFFER_SIZE];
    uint32_t    num_of_bits[2];
}               t_ssl_md5_ctx;


void        ft_ssl_md5_init(t_ssl_md5_ctx *context);
void        ft_ssl_md5_update(t_ssl_md5_ctx *context, t_byte *str, unsigned int str_len);
void        ft_ssl_md5_final(t_byte digest[16], t_ssl_md5_ctx *context);
void        ft_ssl_md5_transform(uint32_t st[4], t_byte buffer[FT_MD5_BUFFER_SIZE]);
void        ft_ssl_md5_encode(t_byte *out, uint32_t *in, unsigned int out_len);
void        ft_ssl_md5_decode(uint32_t *out, t_byte *in, unsigned int in_len);
void        ft_ssl_md5_make_string(unsigned char digest[16], char *result, unsigned int len);

#endif
