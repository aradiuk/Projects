#ifndef __FT_SSL_SHA256_H__
# define __FT_SSL_SHA256_H__

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

# define FT_SHA256_BUFFER_SIZE 64

# define SHR(a, b) ((b) >> (a))
# define ROT_R(a, b) (((b) >> (a)) | ((b) << (32 - (a))))

# define SHA256_CHANGE_SCH0(a) (ROT_R(2, a) ^ ROT_R(13, a) ^ ROT_R(22, a))
# define SHA256_CHANGE_SCH1(a) (ROT_R(6, a) ^ ROT_R(11, a) ^ ROT_R(25, a))
# define SHA256_PREP_SCH0(a) (ROT_R(7, a) ^ ROT_R(18, a) ^ SHR(3, a))
# define SHA256_PREP_SCH1(a) (ROT_R(17, a) ^ ROT_R(19, a) ^ SHR(10, a))
# define SHA256_CH(a, b, c) (((a) & ((b) ^ (c))) ^ (c))
# define SHA256_MAJ(a, b, c) (((a) & ((b) | (c))) | ((b) & (c)))

typedef unsigned char t_byte;

typedef struct	s_ssl_sha256_context
{
	uint32_t	st[8];
	t_byte		buffer[FT_SHA256_BUFFER_SIZE];
	uint32_t	num_of_bits[2];
}				t_ssl_sha256_ctx;

void	ft_ssl_sha256_init(t_ssl_sha256_ctx *context);
void	ft_ssl_sha256_update(t_ssl_sha256_ctx *context, t_byte *str, unsigned int str_len);
void	ft_ssl_sha256_final(t_byte digest[32], t_ssl_sha256_ctx *context);
void	ft_ssl_sha224_init(t_ssl_sha256_ctx *context);
void	ft_ssl_sha224_update(t_ssl_sha256_ctx *context, t_byte *str, unsigned int str_len);
void	ft_ssl_sha224_final(t_byte digest[32], t_ssl_sha256_ctx *context);
void	ft_ssl_sha256_transform(uint32_t st[8], t_byte buffer[FT_SHA256_BUFFER_SIZE]);
void	ft_ssl_sha256_prepare_schedule(uint32_t decoded[FT_SHA256_BUFFER_SIZE]);
void	ft_ssl_sha256_init_temp_st(uint32_t temp_st[8], uint32_t st[8]);
void	ft_ssl_sha256_main_hash(uint32_t st[8], uint32_t decoded[FT_SHA256_BUFFER_SIZE]);
void	ft_ssl_sha256_initermediate_st(uint32_t st[8], uint32_t temp_st[8]);
void	ft_ssl_sha256_decode(uint32_t *out, t_byte *in, unsigned int in_len);
void	ft_ssl_sha256_encode(t_byte *out, uint32_t *in, unsigned int in_len);
void	ft_ssl_sha256_encode_num_of_bits(t_byte *out, uint32_t *in, unsigned int in_len);
void	ft_ssl_sha256_make_string(unsigned char digest[16], char *result);

#endif
