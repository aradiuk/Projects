/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:00:32 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/24 16:00:33 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	obj_alloc(t_rtv *rtv)
{
	rtv->num[0] = 2;
	rtv->num[1] = 1;
	rtv->num[2] = 1;
	rtv->num[3] = 1;
	rtv->plane = (t_plane *)malloc(sizeof(t_plane) * rtv->num[0]);
	rtv->sphere = (t_sphere *)malloc(sizeof(t_sphere) * rtv->num[1]);
	rtv->cyl = (t_cylinder *)malloc(sizeof(t_cylinder) * rtv->num[2]);
	rtv->cone = (t_cone *)malloc(sizeof(t_cone) * rtv->num[3]);
	rtv->comp = (t_composed *)malloc(sizeof(t_composed));
}

void	plane_params(t_rtv *rtv)
{
	rtv->plane[0].pos = vec3_create(0, -1, -50);
	rtv->plane[0].normal = vec3_norm(vec3_create(0, 0, 1));
	rtv->plane[0].color.rgb = vec3_create(192, 192, 192);
	rtv->plane[1].pos = vec3_create(0, -20, -35);
	rtv->plane[1].normal = vec3_norm(vec3_create(0, 1, 0));
	rtv->plane[1].color.rgb = vec3_create(192, 192, 192);
}

void	sphere_params(t_rtv *rtv)
{
	rtv->sphere[0].pos = vec3_create(0, 0, -10);
	rtv->sphere[0].rad = 7.0;
	rtv->sphere[0].color.rgb = vec3_create(232, 187, 139);
}

void	cylinder_params(t_rtv *rtv)
{
	rtv->cyl[0].pos = vec3_create(20, 0, -10);
	rtv->cyl[0].axis = vec3_norm(vec3_create(0, 1, 0));
	rtv->cyl[0].rad = 10.0;
	rtv->cyl[0].color.rgb = vec3_create(60, 99, 120);
}

void	cone_params(t_rtv *rtv)
{
	rtv->cone[0].pos = vec3_create(10, 0, -30);
	rtv->cone[0].axis = vec3_norm(vec3_create(1, 1, 0));
	rtv->cone[0].angle = 20. * (double)M_PI / 180.;
	rtv->cone[0].color.rgb = vec3_create(215, 173, 63);
}
