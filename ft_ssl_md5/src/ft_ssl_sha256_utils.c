/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:26:50 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/08 11:26:52 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	ft_ssl_sha256_decode(uint32_t *out, t_byte *in, unsigned int in_len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < in_len)
	{
		out[i] = (((uint32_t)in[j]) << 24) |
					(((uint32_t)in[j + 1]) << 16) |
					(((uint32_t)in[j + 2]) << 8) |
					((uint32_t)in[j + 3]);
		++i;
		j += 4;
	}
}

void	ft_ssl_sha256_encode(t_byte *out, uint32_t *in, unsigned int in_len)
{
	unsigned int	i;
	unsigned int	j;

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

void	ft_ssl_sha256_encode_num_of_bits(t_byte *out, uint32_t *in,
						unsigned int in_len)
{
	unsigned int	i;
	unsigned int	j;

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
