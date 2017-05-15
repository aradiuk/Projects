/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 15:56:36 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/09 15:56:36 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	cl_t_count(t_ray *ray, double disc, double b, double a)
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

t_vec3	cl_disk_center(t_cylinder *cyl, t_ray *ray)
{
	double	t;
	t_vec3	result;

	t = vec3_dp(vec3_sub(ray->v, cyl->pos), cyl->axis);
	result = vec3_add(cyl->pos, vec3_mult(cyl->axis, t));
	return (result);
}

double	cl_intersection_find(t_rtv *rtv, t_cylinder *cyl, t_ray *ray)
{
	double	b;
	double	a;
	double	c;
	double	disc;
	t_vec3	cam_to_cyl;

	cam_to_cyl = vec3_sub(ray->pos, cyl->pos);
	cyl->a = vec3_sub(ray->dir, vec3_mult(cyl->axis,
								vec3_dp(cyl->axis, ray->dir)));
	cyl->c = vec3_sub(cam_to_cyl, vec3_mult(cyl->axis,
								vec3_dp(cyl->axis, cam_to_cyl)));
	a = vec3_dp(cyl->a, cyl->a);
	c = vec3_dp(cyl->c, cyl->c) - cyl->rad * cyl->rad;
	b = vec3_dp(cyl->a, cyl->c);
	disc = b * b - a * c;
	if (disc < 0.0 || cl_t_count(ray, disc, b, a) == -1)
		return (0);
	if (rtv->type == 2)
		cylinder_vectors(rtv, cyl, ray);
	return (ray->t);
}

void	cylinder_entry(t_rtv *rtv, int i)
{
	int		x;
	int		y;
	t_vec3	pixel_coor;

	cylinder_params(rtv);
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
			if (cl_intersection_find(rtv, &rtv->cyl[i], &rtv->cam->ray) != 0)
				ipp_fill(rtv, x, y, color_count(rtv, rtv->cyl->color));
			x++;
		}
		y++;
	}
}
