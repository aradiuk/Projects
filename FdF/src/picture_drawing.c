/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 10:47:40 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/15 10:47:41 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	swap_points(t_fdf *fdf, int coords_points)
{
	int temp;

	if (coords_points == 0)
	{
		temp = fdf->line->x0;
		fdf->line->x0 = fdf->line->y0;
		fdf->line->y0 = temp;
		temp = fdf->line->x1;
		fdf->line->x1 = fdf->line->y1;
		fdf->line->y1 = temp;
	}
	else
	{
		temp = fdf->line->x0;
		fdf->line->x0 = fdf->line->x1;
		fdf->line->x1 = temp;
		temp = fdf->line->y0;
		fdf->line->y0 = fdf->line->y1;
		fdf->line->y1 = temp;
	}
}

void	draw_lines(t_fdf *fdf)
{
	int	delta_x;
	int delta_y;
	int error;
	int y;
	int x;

	delta_x = abs(fdf->line->x1 - fdf->line->x0);
	delta_y = abs(fdf->line->y1 - fdf->line->y0);
	error = 0;
	x = fdf->line->x0;
	y = fdf->line->y0;
	while (x < fdf->line->x1)
	{
		if (fdf->swap->swapped == 0)
			ipp_fill(fdf, x, y);
		else
			ipp_fill(fdf, y, x);
		error += delta_y;
		if (2 * error >= delta_x)
		{
			y += fdf->swap->up_down;
			error -= delta_x;
		}
		x++;
	}
}

void	draw_octant(t_fdf *fdf)
{
	int dx;
	int dy;

	fdf->swap->up_down = 1;
	fdf->swap->swapped = 0;
	dx = abs(fdf->line->x1 - fdf->line->x0);
	dy = abs(fdf->line->y1 - fdf->line->y0);
	if (dy > dx)
	{
		swap_points(fdf, 0);
		fdf->swap->swapped = 1;
	}
	if (fdf->line->x0 > fdf->line->x1)
		swap_points(fdf, 1);
	if (fdf->line->y0 > fdf->line->y1)
		fdf->swap->up_down = -1;
	draw_lines(fdf);
}

void	view_check(t_fdf *fdf)
{
	int	i;
	int j;

	i = 0;
	fdf->img->image = mlx_new_image(fdf->mlx->mlx, WIDTH, HEIGHT);
	fdf->img->ipp = mlx_get_data_addr(fdf->img->image, &fdf->img->bpp,
									&fdf->img->size_line, &fdf->img->endian);
	while (i++ < fdf->map->lines)
	{
		j = 0;
		while (j++ < fdf->map->symbols)
			draw_start(fdf, i - 1, j - 1);
	}
	mlx_put_image_to_window(fdf->mlx->mlx, fdf->mlx->window,
							fdf->img->image, 0, 0);
	mlx_string_put(fdf->mlx->mlx, fdf->mlx->window, 0, 0, 255, "Use arrows to"
		" rotate along X or Y axis, 1 or 3 on NumPad to rotate along Z axis");
	mlx_string_put(fdf->mlx->mlx, fdf->mlx->window, 0, 15, 255, "Use + or - to"
		" zoom in or out");
	mlx_string_put(fdf->mlx->mlx, fdf->mlx->window, 0, 30, 255, "Use 0 or . to"
			" zoom in or out on Z axis");
	mlx_string_put(fdf->mlx->mlx, fdf->mlx->window, 0, 45, 255, "Use \"cross\""
			" on NumPad to move the image and 5 to center it");
}

void	draw_start(t_fdf *fdf, int i, int j)
{
	if (j < fdf->map->symbols - 1)
	{
		fdf->line->i0 = i;
		fdf->line->j0 = j;
		fdf->line->x0 = fdf->map->point[i][j].x;
		fdf->line->y0 = fdf->map->point[i][j].y;
		fdf->line->x1 = fdf->map->point[i][j + 1].x;
		fdf->line->y1 = fdf->map->point[i][j + 1].y;
		fdf->line->i1 = i;
		fdf->line->j1 = j + 1;
		draw_octant(fdf);
	}
	if (i < fdf->map->lines - 1)
	{
		fdf->line->i0 = i;
		fdf->line->j0 = j;
		fdf->line->x0 = fdf->map->point[i][j].x;
		fdf->line->y0 = fdf->map->point[i][j].y;
		fdf->line->x1 = fdf->map->point[i + 1][j].x;
		fdf->line->y1 = fdf->map->point[i + 1][j].y;
		fdf->line->i1 = i + 1;
		fdf->line->j1 = j;
		draw_octant(fdf);
	}
}
