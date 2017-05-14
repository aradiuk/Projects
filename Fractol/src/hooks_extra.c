/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:11:31 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/03 14:11:32 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	xyz_output(t_fract *fr, int x, int y)
{
	fr->out.itoaed[3] = ft_itoa(x);
	fr->out.itoaed[4] = ft_itoa(y);
	if (fr->fr_d.zoom >= 2147483467)
		fr->out.itoaed[5] = ft_strdup("Maxed");
	else
		fr->out.itoaed[5] = ft_itoa_double(fr->fr_d.zoom);
	fr->out.out[3] = ft_strjoin("x: ", fr->out.itoaed[3]);
	fr->out.out[4] = ft_strjoin("y: ", fr->out.itoaed[4]);
	fr->out.out[5] = ft_strjoin("zoom: ", fr->out.itoaed[5]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, 0, 41, 0xFFFFFF, fr->out.out[3]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, 0, 56, 0xFFFFFF, fr->out.out[4]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, 0, 71, 0xFFFFFF, fr->out.out[5]);
	free(fr->out.itoaed[3]);
	free(fr->out.itoaed[4]);
	free(fr->out.itoaed[5]);
	free(fr->out.out[3]);
	free(fr->out.out[4]);
	free(fr->out.out[5]);
}

void	ship_vary(int x, int y, t_fract *fr)
{
	if (fr->type == 2)
	{
		if (fr->hooked[0] % 2 == 1)
		{
			fr->fr_d.newre = 0;
			fr->fr_d.newim = 0;
			fr->fr_d.newre += (double)(x - WIDTH / 2) / (double)WIDTH;
			fr->fr_d.newim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
			fr->out.mouse = 1;
		}
		if (fr->hooked[1] % 2 == 1 && (fr->out.r = 1))
		{
			fr->fr_d.newre = 0;
			fr->fr_d.newim = 0;
			fr->fr_d.newre += (double)(x - WIDTH / 2) / (double)WIDTH;
		}
		if (fr->hooked[2] % 2 == 1 && (fr->out.i = 1))
		{
			fr->fr_d.newre = 0;
			fr->fr_d.newim = 0;
			fr->fr_d.newim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
		}
	}
}

void	brain_vary(int x, int y, t_fract *fr)
{
	if (fr->type == 3)
	{
		if (fr->hooked[0] % 2 == 1)
		{
			fr->fr_d.cre = BRAIN_RE;
			fr->fr_d.cim = BRAIN_IM;
			fr->fr_d.cre += (double)(x - WIDTH / 2) / (double)WIDTH;
			fr->fr_d.cim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
			fr->out.mouse = 1;
		}
		if (fr->hooked[1] % 2 == 1 && (fr->out.r = 1) &&
			(fr->fr_d.cre = BRAIN_RE))
			fr->fr_d.cre += (double)(x - WIDTH / 2) / (double)WIDTH;
		if (fr->hooked[2] % 2 == 1 && (fr->out.i = 1) &&
			(fr->fr_d.cim = BRAIN_IM))
			fr->fr_d.cim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
	}
}

void	colors(t_fract *fr)
{
	fr->fr_d.color_s[0].r = 0x00;
	fr->fr_d.color_s[0].g = 0x00;
	fr->fr_d.color_s[0].b = 0x00;
	fr->fr_d.color_e[0].r = 0xff;
	fr->fr_d.color_e[0].g = 0xff;
	fr->fr_d.color_e[0].b = 0xff;
	fr->fr_d.color_s[1].r = 0xc0;
	fr->fr_d.color_s[1].g = 0x24;
	fr->fr_d.color_s[1].b = 0x25;
	fr->fr_d.color_e[1].r = 0xf0;
	fr->fr_d.color_e[1].g = 0xcb;
	fr->fr_d.color_e[1].b = 0x35;
	fr->fr_d.color_s[2].r = 0x2c;
	fr->fr_d.color_s[2].g = 0x3e;
	fr->fr_d.color_s[2].b = 0x50;
	fr->fr_d.color_e[2].r = 0x34;
	fr->fr_d.color_e[2].g = 0x98;
	fr->fr_d.color_e[2].b = 0xdb;
	fr->fr_d.color_e[3].r = 0xff;
	fr->fr_d.color_e[3].g = 0xd8;
	fr->fr_d.color_e[3].b = 0x9b;
	fr->fr_d.color_s[3].r = 0x19;
	fr->fr_d.color_s[3].g = 0x54;
	fr->fr_d.color_s[3].b = 0x7b;
	colors_1(fr);
}

void	colors_1(t_fract *fr)
{
	fr->fr_d.color_e[4].r = 0xcc;
	fr->fr_d.color_e[4].g = 0xcc;
	fr->fr_d.color_e[4].b = 0xb2;
	fr->fr_d.color_s[4].r = 0x75;
	fr->fr_d.color_s[4].g = 0x75;
	fr->fr_d.color_s[4].b = 0x19;
}
