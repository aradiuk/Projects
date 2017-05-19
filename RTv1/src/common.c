/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 15:50:35 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/09 15:50:36 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		cross_exit(void *a)
{
	if (a)
		exit(0);
	return (0);
}

int		key_hook(int keycode, t_rtv *rtv)
{
	if (keycode == 83)
		camera_rotation(rtv, -1);
	if (keycode == 85)
		camera_rotation(rtv, 1);
	if (keycode == 86)
		camera_rotation(rtv, -2);
	if (keycode == 88)
		camera_rotation(rtv, 2);
	if (keycode == 89)
		camera_rotation(rtv, 3);
	if (keycode == 92)
		camera_rotation(rtv, -3);
	if (keycode == 1)
		camera_rotation(rtv, -4);
	if (keycode == 13)
		camera_rotation(rtv, 4);
	if (keycode == 0)
		camera_rotation(rtv, -5);
	if (keycode == 2)
		camera_rotation(rtv, 5);
	keycode == 12 ? camera_rotation(rtv, 6) : 0;
	keycode == 14 ? camera_rotation(rtv, -6) : 0;
	keycode == 87 ? camera_rotation(rtv, 0) : 0;
	keycode == 53 ? exit(0) : 0;
	return (0);
}

int		color_count(t_rtv *rtv, t_color color)
{
	int		i;
	t_ray	ray;

	i = 0;
	ray = rtv->cam->ray;
	while (i < LIGHT_SOURCES)
	{
		color.r += color.rgb.x * DIFF_R * (1 -
				rtv->light[i].block) * vec3_dp(ray.n[i], ray.l[i]) +
				rtv->light[i].color.rgb.x * SP_R * (1 - rtv->light[i].block) *
				pow(vec3_dp(ray.n[i], ray.h[i]), GL);
		color.g += color.rgb.y * DIFF_G * (1 -
				rtv->light[i].block) * vec3_dp(ray.n[i], ray.l[i]) +
				rtv->light[i].color.rgb.y * SP_G * (1 - rtv->light[i].block) *
				pow(vec3_dp(ray.n[i], ray.h[i]), GL);
		color.b += color.rgb.z * DIFF_B * (1 -
				rtv->light[i].block) * vec3_dp(ray.n[i], ray.l[i]) +
				rtv->light[i].color.rgb.z * SP_B * (1 - rtv->light[i].block) *
				pow(vec3_dp(ray.n[i], ray.h[i]), GL);
		i++;
	}
	shadow_count(rtv, &color.r, &color.g, &color.b);
	color.final_color = ((int)fmin(255, color.r) << 16) +
					((int)fmin(255, color.g) << 8) + (int)fmin(255, color.b);
	return (color.final_color);
}

void	matrices(t_rtv *rtv)
{
	rtv->mxs.rot_x_cam = x_rot(rtv->mxs.cam_angle.x);
	rtv->mxs.rot_y_cam = y_rot(rtv->mxs.cam_angle.y);
	rtv->mxs.rot_z_cam = z_rot(rtv->mxs.cam_angle.z);
	rtv->mxs.rot_x_dir = x_rot(rtv->mxs.dir_angle.x);
	rtv->mxs.rot_y_dir = y_rot(rtv->mxs.dir_angle.y);
	rtv->mxs.rot_z_dir = z_rot(rtv->mxs.dir_angle.z);
	rtv->mxs.rot_cam = m_mult(m_mult(rtv->mxs.rot_x_cam, rtv->mxs.rot_y_cam),
															rtv->mxs.rot_z_cam);
	rtv->mxs.rot_dir = m_mult(m_mult(rtv->mxs.rot_x_dir, rtv->mxs.rot_y_dir),
															rtv->mxs.rot_z_dir);
}

void	common(t_rtv *rtv)
{
	rtv->mlx->mlx = mlx_init();
	rtv->mlx->window = mlx_new_window(rtv->mlx->mlx, WIDTH, HEIGHT,
													rtv->types[rtv->type]);
	new_image(rtv);
	mlx_hook(rtv->mlx->window, 2, 3, key_hook, rtv);
	mlx_hook(rtv->mlx->window, 17, 1L << 17, cross_exit, rtv);
	mlx_loop(rtv->mlx->mlx);
}
