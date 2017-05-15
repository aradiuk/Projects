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

void	plane_params(t_rtv *rtv)
{
	rtv->num[0] = 2;
	rtv->plane = (t_plane *)malloc(sizeof(t_plane) * rtv->num[0]);
	rtv->plane[0].pos = vec3_create(0, -1, -50);
	rtv->plane[0].normal = vec3_norm(vec3_create(0, 0, 1));
	rtv->plane[0].color.rgb = vec3_create(192, 192, 192);
	rtv->plane[1].pos = vec3_create(0, -15, -35);
	rtv->plane[1].normal = vec3_norm(vec3_create(0, 1, 0));
	rtv->plane[1].color.rgb = vec3_create(192, 192, 192);
}

void	sphere_params(t_rtv *rtv)
{
	rtv->num[1] = 1;
	rtv->sphere = (t_sphere *)malloc(sizeof(t_sphere) * rtv->num[1]);
	rtv->sphere[0].pos = vec3_create(0, 0, -10);
	rtv->sphere[0].rad = 5.0;
	rtv->sphere[0].color.rgb = vec3_create(204, 102, 0);
}

void	cylinder_params(t_rtv *rtv)
{
	rtv->num[2] = 1;
	rtv->cyl = (t_cylinder *)malloc(sizeof(t_cylinder) * rtv->num[2]);
	rtv->cyl[0].pos = vec3_create(10, 0, -10);
	rtv->cyl[0].axis = vec3_norm(vec3_create(0, 1, 0));
	rtv->cyl[0].rad = 2.0;
	rtv->cyl[0].color.rgb = vec3_create(0, 102, 204);
}

void	cone_params(t_rtv *rtv)
{
	rtv->num[3] = 1;
	rtv->cone = (t_cone *)malloc(sizeof(t_cone) * rtv->num[3]);
	rtv->cone[0].pos = vec3_create(10, 0, -30);
	rtv->cone[0].axis = vec3_norm(vec3_create(1, 1, 0));
	rtv->cone[0].angle = 20. * (double)M_PI / 180.;
	rtv->cone[0].color.rgb = vec3_create(0, 153, 76);
}

void	cam_params(t_rtv *rtv)
{
	rtv->cam->pos = vec3_create(0. / WIDTH, 0 / HEIGHT, 100);
	rtv->light[0].pos = vec3_create(15, 10, 50);
	rtv->light[0].color.rgb = vec3_create(100, 100, 100);
	rtv->light[1].pos = vec3_create(-20, 5, 0);
	rtv->light[1].color.rgb = vec3_create(100, 100, 100);
	matrices(rtv);
	rtv->cam->start = rtv->cam->pos;
	rtv->cam->pos = m_apply(rtv->mxs.rot_cam, rtv->cam->pos);
	rtv->cam->ray.pos = rtv->cam->pos;
}
