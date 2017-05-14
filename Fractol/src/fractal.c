/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 14:16:41 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/06 17:32:58 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		gradient(t_comp fr_d, int i)
{
	double	frac;
	t_color	color;
	int		color_i;

	if (fr_d.lsd_on == 0)
	{
		fr_d.lsd[0] = 1;
		fr_d.lsd[1] = 1;
		fr_d.lsd[2] = 1;
	}
	else
	{
		fr_d.lsd[0] = 0.1 * (double)fr_d.max_iter;
		fr_d.lsd[1] = 0.1 * (double)fr_d.max_iter;
		fr_d.lsd[2] = 0.1 * (double)fr_d.max_iter;
	}
	frac = ((double)i / (double)fr_d.max_iter);
	color.r = (int)((fr_d.color_e[fr_d.color].r - fr_d.color_s[fr_d.color].r) *
			frac * fr_d.lsd[0] + fr_d.color_s[fr_d.color].r);
	color.g = (int)((fr_d.color_e[fr_d.color].g - fr_d.color_s[fr_d.color].g) *
			frac * fr_d.lsd[1] + fr_d.color_s[fr_d.color].g);
	color.b = (int)((fr_d.color_e[fr_d.color].b - fr_d.color_s[fr_d.color].b) *
			frac * fr_d.lsd[2] + fr_d.color_s[fr_d.color].b);
	color_i = ((color.r << 16) | (color.g << 8) | (color.b));
	return (color_i);
}

void	ipp_fill(t_thread *data, int x, int y, int color)
{
	*((int *)(data->fr.mlx->ipp + x * data->fr.mlx->bpp / 8 +
			y * data->fr.mlx->size_line)) = color;
}

void	params_type(int type, t_comp *fr_d, int x, int y)
{
	if (type == 0 || type == 3 || type == 4 || type == 5)
	{
		fr_d->newre = 1.5 * (x - WIDTH / 2) / (0.5 * fr_d->zoom * WIDTH)
																+ fr_d->move_x;
		fr_d->newim = (y - HEIGHT / 2) / (0.5 * fr_d->zoom * HEIGHT)
																+ fr_d->move_y;
	}
	if (type == 1 || type == 2)
	{
		fr_d->pr = 1.5 * (x - WIDTH / 2) / (0.5 * fr_d->zoom * WIDTH)
																+ fr_d->move_x;
		fr_d->pi = (y - HEIGHT / 2) / (0.5 * fr_d->zoom * HEIGHT)
																+ fr_d->move_y;
	}
}

void	*fractal(void *data)
{
	int		x;
	int		y;
	int		i;
	int		color;
	t_comp	fr_d;

	y = ((t_thread *)data)->start;
	fr_d = ((t_thread *)data)->fr.fr_d;
	while (y < ((t_thread *)data)->end)
	{
		x = 0;
		while (x < WIDTH)
		{
			params_type(((t_thread *)data)->fr.type, &fr_d, x, y);
			i = algorithm(fr_d, ((t_thread *)data)->fr.type);
			color = gradient(fr_d, i);
			ipp_fill((t_thread *)data, x, y, color);
			x++;
		}
		y++;
	}
	free(data);
	pthread_exit(data);
}

int		algorithm(t_comp fr_d, int type)
{
	int		i;
	double	oldre;
	double	oldim;

	i = 0;
	while (i < fr_d.max_iter)
	{
		oldre = fr_d.newre;
		oldim = fr_d.newim;
		if (type == 2 || type == 3)
		{
			oldre = fabs(fr_d.newre);
			oldim = fabs(fr_d.newim);
		}
		fr_d.newre = oldre * oldre - oldim * oldim + fr_d.cre + fr_d.pr;
		fr_d.newim = 2 * oldre * oldim + fr_d.cim + fr_d.pi;
		if (type == 4 || type == 5)
			julia_3_4(&fr_d, type, &oldre, &oldim);
		if ((fr_d.newre * fr_d.newre + fr_d.newim * fr_d.newim) > 4)
			return (i);
		i++;
	}
	return (1);
}
