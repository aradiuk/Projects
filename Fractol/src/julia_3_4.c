/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_3_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 14:17:28 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/04 14:17:30 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		julias(char *str, t_fract *fr)
{
	if (ft_strcmp(str, "julia") == 0)
	{
		fr->fr_d.cre = JULIA_RE;
		fr->fr_d.cim = JULIA_IM;
		return (0);
	}
	if (ft_strcmp(str, "brain") == 0)
	{
		fr->fr_d.cre = BRAIN_RE;
		fr->fr_d.cim = BRAIN_IM;
		return (3);
	}
	if (ft_strcmp(str, "julia_3") == 0)
	{
		fr->fr_d.cre = 0.4;
		return (4);
	}
	if (ft_strcmp(str, "julia_4") == 0)
	{
		fr->fr_d.cre = 0.484;
		fr->fr_d.cim = 0;
		return (5);
	}
	return (0);
}

void	julia_3_4_vary(int x, int y, t_fract *fr)
{
	if (fr->type == 4 || fr->type == 5)
	{
		if (fr->hooked[0] % 2 == 1 && (fr->fr_d.cre = 0.42))
		{
			fr->fr_d.cim = 0;
			fr->fr_d.cre += (double)(x - WIDTH / 2) / (double)WIDTH;
			fr->fr_d.cim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
			fr->out.mouse = 1;
		}
		if (fr->hooked[1] % 2 == 1 && (fr->out.r = 1) &&
			(fr->fr_d.cre = 0.42))
			fr->fr_d.cre += (double)(x - WIDTH / 2) / (double)WIDTH;
		if (fr->hooked[2] % 2 == 1 && (fr->out.i = 1) &&
			(fr->fr_d.cim = 0))
			fr->fr_d.cim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
	}
}

void	julia_3_4(t_comp *fr_d, int type, double *oldre, double *oldim)
{
	if (type == 4)
	{
		fr_d->newre = *oldre * *oldre * *oldre - 3 * *oldre * *oldim * *oldim +
													fr_d->cre + fr_d->pr;
		fr_d->newim = 3 * *oldre * *oldre * *oldim - *oldim * *oldim * *oldim +
														fr_d->cim + fr_d->pi;
	}
	if (type == 5)
	{
		fr_d->newre = *oldre * *oldre * *oldre * *oldre +
					*oldim * *oldim * *oldim * *oldim -
					4 * *oldre * *oldre * *oldim * *oldim +
														fr_d->cre + fr_d->pr;
		fr_d->newim = 4 * *oldre * *oldim * (*oldre * *oldre - *oldim * *oldim)
														+ fr_d->cim + fr_d->pi;
	}
}

void	free_func(t_fract *fr)
{
	free(fr->types[0]);
	free(fr->types[1]);
	free(fr->types[2]);
	free(fr->types[3]);
	free(fr->types[4]);
	free(fr->types[5]);
	free(fr->types[6]);
	free(fr->types);
	free(fr->mlx);
	free(fr);
}
