/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 18:06:35 by aradiuk           #+#    #+#             */
/*   Updated: 2017/05/09 18:06:36 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	find_max(double *t_object, int size)
{
	int		i;
	double	t;

	i = 0;
	t = 0;
	while (i < size)
	{
		if (t_object[i] > t)
			t = t_object[i];
		i++;
	}
	return (t);
}

double	planes_intersection(t_rtv *rtv, t_ray *ray)
{
	int		i;
	double	t;

	i = -1;
	rtv->comp->plane_num = 0;
	if (rtv->num[0] == 0)
		return (0);
	rtv->comp->plane_t = (double *)malloc(sizeof(double) * rtv->num[0]);
	while (++i < rtv->num[0])
		rtv->comp->plane_t[i] = p_intersection_find(rtv, &rtv->plane[i], ray);
	t = find_max(rtv->comp->plane_t, rtv->num[0]);
	i = 0;
	while (i < rtv->num[0])
	{
		if (rtv->comp->plane_t[i] <= t && rtv->comp->plane_t[i] != 0)
		{
			t = rtv->comp->plane_t[i];
			rtv->comp->plane_num = i;
		}
		i++;
	}
	free(rtv->comp->plane_t);
	return (t);
}

double	spheres_intersection(t_rtv *rtv, t_ray *ray)
{
	int		i;
	double	t;

	i = -1;
	rtv->comp->sphere_num = 0;
	if (rtv->num[1] == 0)
		return (0);
	rtv->comp->sphere_t = (double *)malloc(sizeof(double) * rtv->num[1]);
	while (++i < rtv->num[1])
		rtv->comp->sphere_t[i] = s_intersection_find(rtv, &rtv->sphere[i], ray);
	t = find_max(rtv->comp->sphere_t, rtv->num[1]);
	i = 0;
	while (i < rtv->num[1])
	{
		if (rtv->comp->sphere_t[i] <= t && rtv->comp->sphere_t[i] != 0)
		{
			t = rtv->comp->sphere_t[i];
			rtv->comp->sphere_num = i;
		}
		i++;
	}
	free(rtv->comp->sphere_t);
	return (t);
}

double	cylinders_intersection(t_rtv *rtv, t_ray *ray)
{
	int		i;
	double	t;

	i = -1;
	rtv->comp->cyl_num = 0;
	if (rtv->num[2] == 0)
		return (0);
	rtv->comp->cyl_t = (double *)malloc(sizeof(double) * rtv->num[2]);
	while (++i < rtv->num[2])
		rtv->comp->cyl_t[i] = cl_intersection_find(rtv, &rtv->cyl[i], ray);
	t = find_max(rtv->comp->cyl_t, rtv->num[2]);
	i = 0;
	while (i < rtv->num[2])
	{
		if (rtv->comp->cyl_t[i] <= t && rtv->comp->cyl_t[i] != 0)
		{
			t = rtv->comp->cyl_t[i];
			rtv->comp->cyl_num = i;
		}
		i++;
	}
	free(rtv->comp->cyl_t);
	return (t);
}

double	cones_intersection(t_rtv *rtv, t_ray *ray)
{
	int		i;
	double	t;

	i = -1;
	rtv->comp->cone_num = 0;
	if (rtv->num[3] == 0)
		return (0);
	rtv->comp->cone_t = (double *)malloc(sizeof(double) * rtv->num[3]);
	while (++i < rtv->num[3])
		rtv->comp->cone_t[i] = cn_intersection_find(rtv, &rtv->cone[i], ray);
	t = find_max(rtv->comp->cone_t, rtv->num[3]);
	i = 0;
	while (i < rtv->num[3])
	{
		if (rtv->comp->cone_t[i] <= t && rtv->comp->cone_t[i] != 0)
		{
			t = rtv->comp->cone_t[i];
			rtv->comp->cone_num = i;
		}
		i++;
	}
	free(rtv->comp->cone_t);
	return (t);
}
