/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 15:56:42 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/09 15:56:42 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cn_t_count(t_ray *ray, double disc, double b, double a)
{
	double	t_p;
	double	t_m;

	t_p = (-b + sqrt(disc)) / a;
	t_m = (-b - sqrt(disc)) / a;
	if (t_m < 0 && t_p < 0)
		return (-1);
	if (t_m < 0 || t_p < 0)
		ray->t = fmax(t_m, t_p);
	else
		ray->t = fmin(t_m, t_p);
	return (0);
}

double	cn_disk_count(t_rtv *rtv)
{
	double	a;
	double	b;
	double	c;

	a = cos(rtv->cone->angle) * cos(rtv->cone->angle) * vec3_dp(rtv->cone->a_c,
			rtv->cone->a_c) - sin(rtv->cone->angle) * sin(rtv->cone->angle) *
			rtv->cone->a_s * rtv->cone->a_s;
	c = cos(rtv->cone->angle) * cos(rtv->cone->angle) * vec3_dp(rtv->cone->c_c,
			rtv->cone->c_c) - sin(rtv->cone->angle) * sin(rtv->cone->angle) *
							rtv->cone->c_s * rtv->cone->c_s;
	b = cos(rtv->cone->angle) * cos(rtv->cone->angle) *
			vec3_dp(rtv->cone->a_c, rtv->cone->c_c) - sin(rtv->cone->angle) *
			sin(rtv->cone->angle) * rtv->cone->a_s * rtv->cone->c_s;
	rtv->cone->a = a;
	rtv->cone->b = b;
	return (b * b - a * c);
}

double	cn_intersection_find(t_rtv *rtv, t_ray *ray)
{
	double	disc;
	t_vec3	cam_to_cone;

	cam_to_cone = vec3_sub(ray->pos, rtv->cone->pos);
	rtv->cone->a_s = vec3_dp(rtv->cone->axis, ray->dir);
	rtv->cone->a_c = vec3_sub(ray->dir, vec3_mult(rtv->cone->axis,
														rtv->cone->a_s));
	rtv->cone->c_s = vec3_dp(rtv->cone->axis, cam_to_cone);
	rtv->cone->c_c = vec3_sub(cam_to_cone, vec3_mult(rtv->cone->axis,
													rtv->cone->c_s));
	disc = cn_disk_count(rtv);
	if (disc < 0.0 || cn_t_count(ray, disc, rtv->cone->b, rtv->cone->a) == -1)
		return (0);
	if (rtv->type == 3)
		cone_vectors(rtv, ray);
	return (ray->t);
}

void	cone_entry(t_rtv *rtv)
{
	int		x;
	int		y;
	t_vec3	pixel_coor;

	cone_params(rtv);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_coor.x = (2 * (x + 0.5) / WIDTH - 1) * ASPECT * tan(FOV / 2);
			pixel_coor.y = (1 - 2 * (y + 0.5) / HEIGHT) * tan(FOV / 2);
			pixel_coor.z = rtv->cam->pos.z - 1;
			rtv->cam->ray.dir = vec3_norm(vec3_sub(pixel_coor,
												rtv->cam->ray.pos));
			if (cn_intersection_find(rtv, &rtv->cam->ray) != 0)
				mlx_pixel_put(rtv->mlx->mlx, rtv->mlx->window, x, y,
							color_count(rtv, rtv->cone->color));
			x++;
		}
		y++;
	}
}
