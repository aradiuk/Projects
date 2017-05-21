/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 15:56:48 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/09 15:56:48 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	p_intersection_find(t_rtv *rtv, t_plane *plane, t_ray *ray)
{
	t_vec3	cam_to_plane;
	double	contained;
	double	denom;

	denom = vec3_dp(plane->normal, ray->dir);
	cam_to_plane = vec3_sub(plane->pos, ray->pos);
	contained = vec3_dp(cam_to_plane, plane->normal);
	ray->t = contained / denom;
	if ((denom <= 0.000001 && denom >= -0.000001) || contained == 0 ||
																	ray->t < 0)
		return (0);
	if (rtv->type == 0)
		plane_vectors(rtv, plane, ray);
	return (ray->t);
}
