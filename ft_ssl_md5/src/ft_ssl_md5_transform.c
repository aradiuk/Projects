/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5_transform.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:26:25 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/08 11:26:27 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static void	ft_ssl_md5_round1(uint32_t st[4], uint32_t dec[16])
{
	FF(st[0], st[1], st[2], st[3], dec[0], S11, 0xd76aa478);
	FF(st[3], st[0], st[1], st[2], dec[1], S12, 0xe8c7b756);
	FF(st[2], st[3], st[0], st[1], dec[2], S13, 0x242070db);
	FF(st[1], st[2], st[3], st[0], dec[3], S14, 0xc1bdceee);
	FF(st[0], st[1], st[2], st[3], dec[4], S11, 0xf57c0faf);
	FF(st[3], st[0], st[1], st[2], dec[5], S12, 0x4787c62a);
	FF(st[2], st[3], st[0], st[1], dec[6], S13, 0xa8304613);
	FF(st[1], st[2], st[3], st[0], dec[7], S14, 0xfd469501);
	FF(st[0], st[1], st[2], st[3], dec[8], S11, 0x698098d8);
	FF(st[3], st[0], st[1], st[2], dec[9], S12, 0x8b44f7af);
	FF(st[2], st[3], st[0], st[1], dec[10], S13, 0xffff5bb1);
	FF(st[1], st[2], st[3], st[0], dec[11], S14, 0x895cd7be);
	FF(st[0], st[1], st[2], st[3], dec[12], S11, 0x6b901122);
	FF(st[3], st[0], st[1], st[2], dec[13], S12, 0xfd987193);
	FF(st[2], st[3], st[0], st[1], dec[14], S13, 0xa679438e);
	FF(st[1], st[2], st[3], st[0], dec[15], S14, 0x49b40821);
}

static void	ft_ssl_md5_round2(uint32_t st[4], uint32_t dec[16])
{
	GG(st[0], st[1], st[2], st[3], dec[1], S21, 0xf61e2562);
	GG(st[3], st[0], st[1], st[2], dec[6], S22, 0xc040b340);
	GG(st[2], st[3], st[0], st[1], dec[11], S23, 0x265e5a51);
	GG(st[1], st[2], st[3], st[0], dec[0], S24, 0xe9b6c7aa);
	GG(st[0], st[1], st[2], st[3], dec[5], S21, 0xd62f105d);
	GG(st[3], st[0], st[1], st[2], dec[10], S22, 0x2441453);
	GG(st[2], st[3], st[0], st[1], dec[15], S23, 0xd8a1e681);
	GG(st[1], st[2], st[3], st[0], dec[4], S24, 0xe7d3fbc8);
	GG(st[0], st[1], st[2], st[3], dec[9], S21, 0x21e1cde6);
	GG(st[3], st[0], st[1], st[2], dec[14], S22, 0xc33707d6);
	GG(st[2], st[3], st[0], st[1], dec[3], S23, 0xf4d50d87);
	GG(st[1], st[2], st[3], st[0], dec[8], S24, 0x455a14ed);
	GG(st[0], st[1], st[2], st[3], dec[13], S21, 0xa9e3e905);
	GG(st[3], st[0], st[1], st[2], dec[2], S22, 0xfcefa3f8);
	GG(st[2], st[3], st[0], st[1], dec[7], S23, 0x676f02d9);
	GG(st[1], st[2], st[3], st[0], dec[12], S24, 0x8d2a4c8a);
}

static void	ft_ssl_md5_round3(uint32_t st[4], uint32_t dec[16])
{
	HH(st[0], st[1], st[2], st[3], dec[5], S31, 0xfffa3942);
	HH(st[3], st[0], st[1], st[2], dec[8], S32, 0x8771f681);
	HH(st[2], st[3], st[0], st[1], dec[11], S33, 0x6d9d6122);
	HH(st[1], st[2], st[3], st[0], dec[14], S34, 0xfde5380c);
	HH(st[0], st[1], st[2], st[3], dec[1], S31, 0xa4beea44);
	HH(st[3], st[0], st[1], st[2], dec[4], S32, 0x4bdecfa9);
	HH(st[2], st[3], st[0], st[1], dec[7], S33, 0xf6bb4b60);
	HH(st[1], st[2], st[3], st[0], dec[10], S34, 0xbebfbc70);
	HH(st[0], st[1], st[2], st[3], dec[13], S31, 0x289b7ec6);
	HH(st[3], st[0], st[1], st[2], dec[0], S32, 0xeaa127fa);
	HH(st[2], st[3], st[0], st[1], dec[3], S33, 0xd4ef3085);
	HH(st[1], st[2], st[3], st[0], dec[6], S34, 0x4881d05);
	HH(st[0], st[1], st[2], st[3], dec[9], S31, 0xd9d4d039);
	HH(st[3], st[0], st[1], st[2], dec[12], S32, 0xe6db99e5);
	HH(st[2], st[3], st[0], st[1], dec[15], S33, 0x1fa27cf8);
	HH(st[1], st[2], st[3], st[0], dec[2], S34, 0xc4ac5665);
}

static void	ft_ssl_md5_round4(uint32_t st[4], uint32_t dec[16])
{
	II(st[0], st[1], st[2], st[3], dec[0], S41, 0xf4292244);
	II(st[3], st[0], st[1], st[2], dec[7], S42, 0x432aff97);
	II(st[2], st[3], st[0], st[1], dec[14], S43, 0xab9423a7);
	II(st[1], st[2], st[3], st[0], dec[5], S44, 0xfc93a039);
	II(st[0], st[1], st[2], st[3], dec[12], S41, 0x655b59c3);
	II(st[3], st[0], st[1], st[2], dec[3], S42, 0x8f0ccc92);
	II(st[2], st[3], st[0], st[1], dec[10], S43, 0xffeff47d);
	II(st[1], st[2], st[3], st[0], dec[1], S44, 0x85845dd1);
	II(st[0], st[1], st[2], st[3], dec[8], S41, 0x6fa87e4f);
	II(st[3], st[0], st[1], st[2], dec[15], S42, 0xfe2ce6e0);
	II(st[2], st[3], st[0], st[1], dec[6], S43, 0xa3014314);
	II(st[1], st[2], st[3], st[0], dec[13], S44, 0x4e0811a1);
	II(st[0], st[1], st[2], st[3], dec[4], S41, 0xf7537e82);
	II(st[3], st[0], st[1], st[2], dec[11], S42, 0xbd3af235);
	II(st[2], st[3], st[0], st[1], dec[2], S43, 0x2ad7d2bb);
	II(st[1], st[2], st[3], st[0], dec[9], S44, 0xeb86d391);
}

void		ft_ssl_md5_transform(uint32_t st[4],
						t_byte buffer[FT_MD5_BUFFER_SIZE])
{
	uint32_t	decoded[16];
	uint32_t	temp_st[4];

	ft_ssl_md5_decode(decoded, buffer, FT_MD5_BUFFER_SIZE);
	temp_st[0] = st[0];
	temp_st[1] = st[1];
	temp_st[2] = st[2];
	temp_st[3] = st[3];
	ft_ssl_md5_round1(temp_st, decoded);
	ft_ssl_md5_round2(temp_st, decoded);
	ft_ssl_md5_round3(temp_st, decoded);
	ft_ssl_md5_round4(temp_st, decoded);
	st[0] += temp_st[0];
	st[1] += temp_st[1];
	st[2] += temp_st[2];
	st[3] += temp_st[3];
	ft_bzero(decoded, sizeof(decoded));
}
