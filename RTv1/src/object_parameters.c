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
	rtv->plane->pos = m_apply(rtv->mxs.multed, vec3_create(0, -15, -35));
//	rtv->plane->pos = vec3_create(0, -15, -35);
	rtv->plane->normal = vec3_norm(vec3_create(0, 1, 0));
	rtv->plane->color.rgb = vec3_create(192, 192, 192);
}

void	sphere_params(t_rtv *rtv)
{
	rtv->sphere->pos = m_apply(rtv->mxs.multed ,vec3_create(0, 0, -10));
//	rtv->sphere->pos = vec3_create(-10, 5, -10);
	rtv->sphere->rad = 5.0;
	rtv->sphere->color.rgb = vec3_create(204, 102, 0);
}

void	cylinder_params(t_rtv *rtv)
{
	rtv->cyl->pos = m_apply(rtv->mxs.multed, vec3_create(10, 0, -10));
//	rtv->cyl->pos = vec3_create(10, 0, -10);
	rtv->cyl->axis = vec3_norm(vec3_create(0, 1, 0));
	rtv->cyl->rad = 5.0;
	rtv->cyl->color.rgb = vec3_create(0, 102, 204);
}

void	cone_params(t_rtv *rtv)
{
	rtv->cone->pos = m_apply(rtv->mxs.multed, vec3_create(10, -2, -20));
//	rtv->cone->pos = vec3_create(10, -2, -20);
	rtv->cone->axis = vec3_norm(vec3_create(1, 1, 0));
	rtv->cone->angle = 15. * (double)M_PI / 180.;
	rtv->cone->color.rgb = vec3_create(0, 153, 76);
}

void	composed_params(t_rtv *rtv)
{
	plane_params(rtv);
	sphere_params(rtv);
	cylinder_params(rtv);
	cone_params(rtv);
}
