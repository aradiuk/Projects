/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 16:24:17 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/06 14:09:14 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	center_coords(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->map->lines)
	{
		j = 0;
		while (j < fdf->map->symbols)
		{
			fdf->map->coord[i][j].x -= fdf->map->symbols / 2;
			fdf->map->coord[i][j].y -= fdf->map->lines / 2;
			fdf->map->coord[i][j].z -= (fabs(fdf->mxs->bounds[4]) +
										fabs(fdf->mxs->bounds[5])) / 2;
			j++;
		}
		i++;
	}
}

void	points_calc(t_fdf *fdf)
{
	t_coord		**cor;
	t_matrix	*mx;
	int			i;
	int			j;

	i = 0;
	cor = fdf->map->coord;
	mx = fdf->mxs->m_final;
	while (i < fdf->map->lines)
	{
		j = 0;
		while (j < fdf->map->symbols)
		{
			fdf->map->point[i][j].x = mx->m[0][0] * cor[i][j].x +
			mx->m[0][1] * cor[i][j].y + mx->m[0][2] * cor[i][j].z + mx->m[0][3];
			fdf->map->point[i][j].y = mx->m[1][0] * cor[i][j].x +
			mx->m[1][1] * cor[i][j].y + mx->m[1][2] * cor[i][j].z + mx->m[1][3];
			fdf->map->point[i][j].z = mx->m[2][0] * cor[i][j].x +
			mx->m[2][1] * cor[i][j].y + mx->m[2][2] * cor[i][j].z + mx->m[2][3];
			fdf->map->point[i][j].color = cor[i][j].color;
			printf("x = %d, y = %d\n", fdf->map->point[i][j].x, fdf->map->point[i][j].y);
			j++;
		}
		i++;
	}
}

void	points_array(t_fdf *fdf)
{
	int	i;
	int j;

	i = 0;
	fdf->map->point = (t_coord **)malloc(sizeof(t_coord *) * fdf->map->lines);
	while (i < fdf->map->lines)
	{
		j = 0;
		fdf->map->point[i] = (t_coord *)malloc(sizeof(t_coord) *
													fdf->map->symbols);
		while (j < fdf->map->symbols)
		{
			fdf->map->point[i][j].x = 0;
			fdf->map->point[i][j].y = 0;
			fdf->map->point[i][j].z = 0;
			j++;
		}
		i++;
	}
	points_calc(fdf);
}

void	ipp_fill(t_fdf *fdf, int x, int y)
{
	int color;

	color = fdf->map->coord[fdf->line->i0][fdf->line->j0].color;
	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	*((int *)(fdf->img->ipp +
			x * fdf->img->bpp / 8 +
			y * fdf->img->size_line)) = color;
}

void	isometric(t_fdf *fdf)
{
	fdf->line = (t_line *)malloc(sizeof(t_line));
	fdf->swap = (t_swap *)malloc(sizeof(t_swap));
	hook_init(fdf);
	center_coords(fdf);
	points_array(fdf);
	view_check(fdf);
}
