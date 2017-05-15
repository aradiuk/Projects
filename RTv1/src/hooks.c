/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 12:08:48 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/29 12:08:49 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ipp_fill(t_rtv *rtv, int x, int y, int color)
{
	*((int *)(rtv->mlx->ipp + x * rtv->mlx->bpp / 8 +
			y * rtv->mlx->size_line)) = color;
}

void	camera_rotation(t_rtv *rtv, int dir)
{
	if (dir == 0)
	{
		rtv->mxs.cam_angle = vec3_create(0, 0, 0);
		rtv->mxs.dir_angle = vec3_create(0, 0, 0);
	}
	if (dir == 1 || dir == -1)
		rtv->mxs.cam_angle.x += dir * ROT_ANGLE;
	if (dir == 2 || dir == -2)
		rtv->mxs.cam_angle.y += dir / 2 * ROT_ANGLE;
	if (dir == 3 || dir == -3)
		rtv->mxs.cam_angle.z += dir / 3 * ROT_ANGLE;
	if (dir == 4 || dir == -4)
		rtv->mxs.dir_angle.x += dir / 4 * ROT_ANGLE;
	if (dir == 5 || dir == -5)
		rtv->mxs.dir_angle.y += dir / 5 * ROT_ANGLE;
	if (dir == 6 || dir == -6)
		rtv->mxs.dir_angle.z += dir / 6 * ROT_ANGLE;
	new_image(rtv);
}

void	new_image(t_rtv *rtv)
{
	rtv->mlx->image = mlx_new_image(rtv->mlx->mlx, WIDTH, HEIGHT);
	rtv->mlx->ipp = mlx_get_data_addr(rtv->mlx->image, &rtv->mlx->bpp,
									&rtv->mlx->size_line, &rtv->mlx->endian);
	cam_params(rtv);
	obj_func(rtv);
	mlx_clear_window(rtv->mlx->mlx, rtv->mlx->window);
	mlx_put_image_to_window(rtv->mlx->mlx, rtv->mlx->window, rtv->mlx->image,
							0, 0);
	mlx_destroy_image(rtv->mlx->mlx, rtv->mlx->image);
}

void	cam_check(t_rtv *rtv)
{
	t_vec3	cam_to_light;
	double	t;
	int		j;
	int		i;

	i = -1;
	j = -1;
	while (++i < LIGHT_SOURCES)
	{
		cam_to_light = vec3_sub(rtv->light[i].pos, rtv->cam->pos);
		rtv->light[i].sh_ray.pos = rtv->cam->pos;
		rtv->light[i].sh_ray.dir = vec3_norm(cam_to_light);
		rtv->light[i].sh_t[0] = planes_intersection(rtv, &rtv->light[i].sh_ray);
		rtv->light[i].sh_t[1] = spheres_intersection(rtv,
													&rtv->light[i].sh_ray);
		rtv->light[i].sh_t[2] = cylinders_intersection(rtv,
													&rtv->light[i].sh_ray);
		rtv->light[i].sh_t[3] = cones_intersection(rtv, &rtv->light[i].sh_ray);
		while (++j < 4)
			if (rtv->light[i].sh_t[j] > vec3_length(cam_to_light))
				rtv->light[i].sh_t[j] = 0;
		t = fmax(fmax(rtv->light[i].sh_t[0], rtv->light[i].sh_t[1]),
				fmax(rtv->light[i].sh_t[2], rtv->light[i].sh_t[3]));
		rtv->light[i].block = t > 0 ? 1 : 0;
	}
}
