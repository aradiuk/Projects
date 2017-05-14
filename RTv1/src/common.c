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

int		key_hook(int keycode, void *param)
{
	
	if (keycode == 53 || param)
		exit(0);
	return (0);
}

int		color_count(t_rtv *rtv, t_color color)
{
	double	r;
	double	g;
	double	b;
	int		i;
	t_ray	ray;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	ray = rtv->cam->ray;
	while (i < LIGHT_SOURCES)
	{
		r += color.rgb.x * (AMBIENT_R + DIFF_R * vec3_dp(ray.n, ray.l[i])) +
		rtv->light[i].color.rgb.x * SPEC_R * pow(vec3_dp(ray.n, ray.h[i]), GLS);
		g += color.rgb.y * (AMBIENT_G + DIFF_G * vec3_dp(ray.n, ray.l[i])) +
		rtv->light[i].color.rgb.y * SPEC_G * pow(vec3_dp(ray.n, ray.h[i]), GLS);
		b += color.rgb.z * (AMBIENT_B + DIFF_B * vec3_dp(ray.n, ray.l[i])) +
		rtv->light[i].color.rgb.z * SPEC_B * pow(vec3_dp(ray.n, ray.h[i]), GLS);
		i++;
	}
	shadow_count(rtv, &r, &g, &b);
	color.final_color = ((int)fmin(255, r) << 16) + ((int)fmin(255, g) << 8) +
															(int)fmin(255, b);
	return (color.final_color);
}

void	cam_vectors(t_rtv *rtv)
{
	rtv->light[0].pos = vec3_create(0, 30, 10);
	rtv->light[0].color.rgb = vec3_create(200, 200, 200);
	rtv->light[1].pos = vec3_create(60, 30, 30);
	rtv->light[1].color.rgb = vec3_create(255, 255, 255);
	rtv->light[2].pos = vec3_create(0, 5, 50);
	rtv->light[2].color.rgb = vec3_create(125, 125, 125);
	rtv->cam->pos = vec3_create(0, 0, -10);
	rtv->cam->gaze = vec3_create(-1, -1, 0);
	rtv->cam->w = vec3_create(0, 0, -1);
	rtv->cam->u = vec3_create(0, 0, 0);
	rtv->cam->v = vec3_create(0, 0, 0);
	rtv->cam->cam_to_g = vec3_sub(rtv->cam->gaze, rtv->cam->pos);
	rtv->cam->w = vec3_norm(vec3_invert(rtv->cam->cam_to_g));
	rtv->cam->u = vec3_norm(vec3_cp(rtv->cam->vec3_y, rtv->cam->w));
	rtv->cam->v = vec3_norm(vec3_cp(rtv->cam->w, rtv->cam->u));
	rtv->cam->ray.pos = rtv->cam->pos;
}

void	common(t_rtv *rtv)
{
	rtv->mlx->mlx = mlx_init();
	rtv->mlx->window = mlx_new_window(rtv->mlx->mlx, WIDTH, HEIGHT,
									rtv->types[rtv->type]);
	cam_vectors(rtv);
	matrices(rtv);
	obj_func(rtv);
	mlx_key_hook(rtv->mlx->window, key_hook, 0);
	mlx_hook(rtv->mlx->window, 17, 1L << 17, cross_exit, rtv);
	mlx_loop(rtv->mlx->mlx);
}
