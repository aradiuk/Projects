/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:13:00 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/26 17:13:01 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane_vectors(t_rtv *rtv, t_plane *plane, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n[0] = plane->normal;
	ray->n[1] = ray->n[0];
	ray->n[2] = ray->n[0];
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], ray->dir));
	if (vec3_dp(ray->n[0], ray->l[0]) < 0)
		ray->n[0] = vec3_invert(ray->n[0]);
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], ray->dir));
	if (vec3_dp(ray->n[1], ray->l[1]) < 0)
		ray->n[1] = vec3_invert(ray->n[1]);
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], ray->dir));
	if (vec3_dp(ray->n[2], ray->l[2]) < 0)
		ray->n[2] = vec3_invert(ray->n[2]);
}

void	sphere_vectors(t_rtv *rtv, t_sphere *sphere, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n[0] = vec3_norm(vec3_sub(ray->v, sphere->pos));
	ray->n[1] = ray->n[0];
	ray->n[2] = ray->n[0];
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], ray->dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], ray->dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], ray->dir));
}

void	cylinder_vectors(t_rtv *rtv, t_cylinder *cyl, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n[0] = vec3_norm(vec3_sub(ray->v, cl_disk_center(cyl, ray)));
	ray->n[1] = ray->n[0];
	ray->n[2] = ray->n[0];
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], ray->dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], ray->dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], ray->dir));
}

void	cone_vectors(t_rtv *rtv, t_cone *cone, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n[0] = vec3_norm(vec3_sub(ray->v,
								vec3_add(cone->pos,
								vec3_mult(cone->axis,
								vec3_length(vec3_sub(ray->v,
													cone->pos)) /
								vec3_dp(cone->axis,
								vec3_norm(vec3_sub(ray->v,
													cone->pos)))))));
	ray->n[1] = ray->n[0];
	ray->n[2] = ray->n[0];
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], rtv->cam->ray.dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], rtv->cam->ray.dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], rtv->cam->ray.dir));
}

void	composed_params(t_rtv *rtv)
{
	rtv->comp = (t_composed *)malloc(sizeof(t_composed));
	rtv->comp->type = 0;
	rtv->comp->plane_num = 0;
	rtv->comp->sphere_num = 0;
	rtv->comp->cyl_num = 0;
	rtv->comp->cone_num = 0;
	plane_params(rtv);
	sphere_params(rtv);
	cylinder_params(rtv);
	cone_params(rtv);
}
