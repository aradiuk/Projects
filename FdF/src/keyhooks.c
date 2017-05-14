/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 11:54:53 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/04 12:36:18 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		exit(0);
	keycode == 123 ? rotate(fdf, -1) : 0;
	keycode == 124 ? rotate(fdf, 1) : 0;
	keycode == 125 ? rotate(fdf, -2) : 0;
	keycode == 126 ? rotate(fdf, 2) : 0;
	keycode == 83 ? rotate(fdf, -3) : 0;
	keycode == 85 ? rotate(fdf, 3) : 0;
	keycode == 84 ? rotate(fdf, -4) : 0;
	keycode == 86 ? rotate(fdf, -5) : 0;
	keycode == 91 ? rotate(fdf, 4) : 0;
	keycode == 88 ? rotate(fdf, 5) : 0;
	keycode == 69 ? rotate(fdf, 6) : 0;
	keycode == 78 ? rotate(fdf, -6) : 0;
	keycode == 87 ? rotate(fdf, 0) : 0;
	keycode == 82 ? rotate(fdf, -7) : 0;
	keycode == 65 ? rotate(fdf, 7) : 0;
	return (0);
}

void	hook_init(t_fdf *fdf)
{
	mlx_hook(fdf->mlx->window, 2, 3, key_hook, fdf);
}

void	rotate(t_fdf *fdf, int direction)
{
	t_matrix	*temp;
	t_matrix	*result;

	if (direction == 1 || direction == -1)
	{
		temp = x_rot_declare(ROT_ON_PRESS * PI * direction / 180);
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
	if (direction == 2 || direction == -2)
	{
		temp = y_rot_declare(ROT_ON_PRESS * PI * direction / 180);
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
	if (direction == 3 || direction == -3)
	{
		temp = z_rot_declare(ROT_ON_PRESS * PI * direction / 180);
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
	translation(fdf, direction);
	mlx_destroy_image(fdf->mlx->mlx, fdf->img->image);
	points_calc(fdf);
	view_check(fdf);
}

void	translation(t_fdf *fdf, double dir)
{
	t_matrix	*temp;
	t_matrix	*result;

	if (dir == 4 || dir == -4)
	{
		temp = m_tr_declare(0, -dir / 4, 0);
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
	if (dir == 5 || dir == -5)
	{
		temp = m_tr_declare(dir / 5, 0, 0);
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
	if (dir == 6 || dir == -6)
	{
		dir = dir > 0 ? 21. / 19. : 0.9;
		temp = m_scale_declare(SCALE * (1 + dir), SCALE * (1 + dir),
							SCALE * (1 + dir));
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
	center_picture(fdf, dir);
}

void	center_picture(t_fdf *fdf, double dir)
{
	t_matrix	*temp;
	t_matrix	*result;

	if (dir == 0)
	{
		temp = matrices(fdf);
		fdf->mxs->m_final = temp;
		points_calc(fdf);
		view_check(fdf);
	}
	if (dir == 7 || dir == -7)
	{
		dir = dir > 0 ? 21. / 19. : 0.9;
		temp = m_scale_declare(1, 1, SCALE * (1 + dir));
		result = mxs_mult(fdf->mxs->m_final, temp);
		fdf->mxs->m_final = result;
	}
}
