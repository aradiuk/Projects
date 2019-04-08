/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:25:59 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/08 11:26:00 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

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

# define FFA(a, b, c, d, x, ac) (a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac)
# define FFB(a, s) (a) = ROT_L ((a), (s))
# define FFC(a, b) (a) += (b)
# define FF(a, b, c, d, x, s, ac) FFA(a, b, c, d, x, ac); FFB(a, s); FFC(a,b);

# define GGA(a, b, c, d, x, ac) (a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac)
# define GGB(a, s) (a) = ROT_L ((a), (s))
# define GGC(a, b) (a) += (b)
# define GG(a, b, c, d, x, s, ac) GGA(a, b, c, d, x, ac); GGB(a, s); GGC(a, b)

# define HHA(a, b, c, d, x, ac) (a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac)
# define HHB(a, s) (a) = ROT_L ((a), (s))
# define HHC(a, b) (a) += (b)
# define HH(a, b, c, d, x, s, ac) HHA(a, b, c, d, x, ac); HHB(a, s); HHC(a, b)

# define IIA(a, b, c, d, x, ac) (a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac)
# define IIB(a, s) (a) = ROT_L ((a), (s))
# define IIC(a, b) (a) += (b)
# define II(a, b, c, d, x, s, ac) IIA(a, b, c, d, x, ac); IIB(a, s); IIC(a, b)

typedef unsigned char	t_byte;

typedef struct	s_ssl_md5_context
{
	uint32_t	st[4];
	t_byte		buffer[FT_MD5_BUFFER_SIZE];
	uint32_t	num_of_bits[2];
}				t_ssl_md5_ctx;

void			ft_ssl_md5_init(t_ssl_md5_ctx *context);
void			ft_ssl_md5_update(t_ssl_md5_ctx *context, t_byte *str,
						unsigned int str_len);
void			ft_ssl_md5_final(t_byte digest[16], t_ssl_md5_ctx *context);
void			ft_ssl_md5_transform(uint32_t st[4],
						t_byte buffer[FT_MD5_BUFFER_SIZE]);
void			ft_ssl_md5_encode(t_byte *out, uint32_t *in,
						unsigned int out_len);
void			ft_ssl_md5_decode(uint32_t *out, t_byte *in,
						unsigned int in_len);
void			ft_ssl_md5_make_string(unsigned char digest[16], char *result,
						unsigned int len);

#endif
