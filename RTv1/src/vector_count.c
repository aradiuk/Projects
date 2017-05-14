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

void	plane_vectors(t_rtv *rtv, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n = rtv->plane->normal;
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], ray->dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], ray->dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], ray->dir));
}

void	sphere_vectors(t_rtv *rtv, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n = vec3_norm(vec3_sub(ray->v, rtv->sphere->pos));
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], ray->dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], ray->dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], ray->dir));
}

void	cylinder_vectors(t_rtv *rtv, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n = vec3_norm(vec3_sub(ray->v, cl_disk_center(rtv, ray)));
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], ray->dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], ray->dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], ray->dir));
}

void	cone_vectors(t_rtv *rtv, t_ray *ray)
{
	ray->v = vec3_add(ray->pos,
								vec3_mult(ray->dir, ray->t));
	ray->n = vec3_norm(vec3_sub(ray->v,
								vec3_add(rtv->cone->pos,
								vec3_mult(rtv->cone->axis,
								vec3_length(vec3_sub(ray->v,
													rtv->cone->pos)) /
								vec3_dp(rtv->cone->axis,
								vec3_norm(vec3_sub(ray->v,
													rtv->cone->pos)))))));
	ray->l[0] = vec3_norm(vec3_sub(rtv->light[0].pos, ray->v));
	ray->h[0] = vec3_norm(vec3_sub(ray->l[0], rtv->cam->ray.dir));
	ray->l[1] = vec3_norm(vec3_sub(rtv->light[1].pos, ray->v));
	ray->h[1] = vec3_norm(vec3_sub(ray->l[1], rtv->cam->ray.dir));
	ray->l[2] = vec3_norm(vec3_sub(rtv->light[2].pos, ray->v));
	ray->h[2] = vec3_norm(vec3_sub(ray->l[2], rtv->cam->ray.dir));
}
