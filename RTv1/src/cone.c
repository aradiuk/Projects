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

double	cn_disk_count(t_cone *cone)
{
	double	a;
	double	b;
	double	c;

	a = cos(cone->angle) * cos(cone->angle) * vec3_dp(cone->a_c,
			cone->a_c) - sin(cone->angle) * sin(cone->angle) *
			cone->a_s * cone->a_s;
	c = cos(cone->angle) * cos(cone->angle) * vec3_dp(cone->c_c,
			cone->c_c) - sin(cone->angle) * sin(cone->angle) *
							cone->c_s * cone->c_s;
	b = cos(cone->angle) * cos(cone->angle) *
			vec3_dp(cone->a_c, cone->c_c) - sin(cone->angle) *
			sin(cone->angle) * cone->a_s * cone->c_s;
	cone->a = a;
	cone->b = b;
	return (b * b - a * c);
}

double	cn_intersection_find(t_rtv *rtv, t_cone *cone, t_ray *ray)
{
	double	disc;
	t_vec3	cam_to_cone;

	cam_to_cone = vec3_sub(ray->pos, cone->pos);
	cone->a_s = vec3_dp(cone->axis, ray->dir);
	cone->a_c = vec3_sub(ray->dir, vec3_mult(cone->axis,
														cone->a_s));
	cone->c_s = vec3_dp(cone->axis, cam_to_cone);
	cone->c_c = vec3_sub(cam_to_cone, vec3_mult(cone->axis,
													cone->c_s));
	disc = cn_disk_count(cone);
	if (disc < 0.0 || cn_t_count(ray, disc, cone->b, cone->a) == -1)
		return (0);
	if (rtv->type == 3)
		cone_vectors(rtv, cone, ray);
	return (ray->t);
}

void	cone_entry(t_rtv *rtv, int i)
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
			pixel_coor.z = rtv->cam->start.z - 1;
			rtv->cam->ray.dir = vec3_norm(vec3_sub(pixel_coor,
												rtv->cam->start));
			rtv->cam->ray.dir = m_apply(rtv->mxs.rot_cam, rtv->cam->ray.dir);
			rtv->cam->ray.dir = m_apply(rtv->mxs.rot_dir, rtv->cam->ray.dir);
			if (cn_intersection_find(rtv, &rtv->cone[i], &rtv->cam->ray) != 0)
				ipp_fill(rtv, x, y, color_count(rtv, rtv->cone->color));
			x++;
		}
		y++;
	}
}
