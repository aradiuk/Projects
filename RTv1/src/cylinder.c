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
