/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 15:56:26 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/09 15:56:30 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	s_t_count(t_ray *ray, double disc, double b, double a)
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

double	s_intersection_find(t_rtv *rtv, t_sphere *sphere, t_ray *ray)
{
	double	disc;
	double	b;
	double	a;
	double	c;

	b = vec3_dp(ray->dir, vec3_sub(ray->pos, sphere->pos));
	a = vec3_dp(ray->dir, ray->dir);
	c = vec3_dp(vec3_sub(ray->pos, sphere->pos),
				vec3_sub(ray->pos, sphere->pos)) -
				sphere->rad * sphere->rad;
	disc = b * b - a * c;
	if (disc < 0.0 || s_t_count(ray, disc, b, a) == -1)
		return (0);
	if (rtv->type == 1)
		sphere_vectors(rtv, sphere, ray);
	return (ray->t);
}

void	sphere_entry(t_rtv *rtv, int i)
{
	int		x;
	int		y;
	t_vec3	pixel_coor;

	sphere_params(rtv);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_coor.x = (2 * (x + 0.5) / WIDTH - 1) * ASPECT * tan(FOV / 2.);
			pixel_coor.y = (1 - 2 * (y + 0.5) / HEIGHT) * tan(FOV / 2.);
			pixel_coor.z = rtv->cam->start.z - 1;
			rtv->cam->ray.dir = vec3_norm(vec3_sub(pixel_coor,
												rtv->cam->start));
			rtv->cam->ray.dir = m_apply(rtv->mxs.rot_cam, rtv->cam->ray.dir);
			rtv->cam->ray.dir = m_apply(rtv->mxs.rot_dir, rtv->cam->ray.dir);
			if (s_intersection_find(rtv, &rtv->sphere[i], &rtv->cam->ray) != 0)
				ipp_fill(rtv, x, y, color_count(rtv, rtv->sphere->color));
			x++;
		}
		y++;
	}
}
