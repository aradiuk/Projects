/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:45:24 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/24 15:45:25 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	*obj_color(t_rtv *rtv, t_ray *ray)
{
	if (rtv->comp->type == 0)
	{
		plane_vectors(rtv, &rtv->plane[rtv->comp->plane_num], ray);
		null_rgb(&rtv->plane[rtv->comp->plane_num].color);
		return (&rtv->plane[rtv->comp->plane_num].color);
	}
	if (rtv->comp->type == 1)
	{
		sphere_vectors(rtv, &rtv->sphere[rtv->comp->sphere_num], ray);
		null_rgb(&rtv->sphere[rtv->comp->sphere_num].color);
		return (&rtv->sphere[rtv->comp->sphere_num].color);
	}
	if (rtv->comp->type == 2)
	{
		cylinder_vectors(rtv, &rtv->cyl[rtv->comp->cyl_num], ray);
		null_rgb(&rtv->cyl[rtv->comp->cyl_num].color);
		return (&rtv->cyl[rtv->comp->cyl_num].color);
	}
	if (rtv->comp->type == 3)
	{
		cone_vectors(rtv, &rtv->cone[rtv->comp->cone_num], ray);
		null_rgb(&rtv->cone[rtv->comp->cone_num].color);
		return (&rtv->cone[rtv->comp->cone_num].color);
	}
	return (0);
}

double	shadowed(t_rtv *rtv, int i)
{
	double	t;
	double	length;
	int		j;

	j = -1;
	length = vec3_length(vec3_sub(rtv->light[i].pos, rtv->cam->ray.v));
	rtv->light[i].sh_ray.v = rtv->cam->ray.v;
	rtv->light[i].sh_ray.pos = vec3_add(rtv->cam->ray.v,
										vec3_mult(rtv->cam->ray.n[i], 0.00001));
	rtv->light[i].sh_ray.dir = rtv->cam->ray.l[i];
	rtv->light[i].sh_t[0] = planes_intersection(rtv, &rtv->light[i].sh_ray);
	rtv->light[i].sh_t[1] = spheres_intersection(rtv, &rtv->light[i].sh_ray);
	rtv->light[i].sh_t[2] = cylinders_intersection(rtv, &rtv->light[i].sh_ray);
	rtv->light[i].sh_t[3] = cones_intersection(rtv, &rtv->light[i].sh_ray);
	while (++j < 4)
		if (rtv->light[i].sh_t[j] > length)
			rtv->light[i].sh_t[j] = 0;
	t = fmax(fmax(rtv->light[i].sh_t[0], rtv->light[i].sh_t[1]),
			fmax(rtv->light[i].sh_t[2], rtv->light[i].sh_t[3]));
	return (t);
}

void	shadow_count(t_rtv *rtv, double *r, double *g, double *b)
{
	int i;

	i = 0;
	*r = fmin(255, *r);
	*g = fmin(255, *g);
	*b = fmin(255, *b);
	while (i < LIGHT_SOURCES)
	{
		if (rtv->type == 4 && rtv->light[i].block == 0 && shadowed(rtv, i) != 0)
		{
			*r *= (1 - SHADOW);
			*g *= (1 - SHADOW);
			*b *= (1 - SHADOW);
		}
		i++;
	}
}

double	cp_intersection_find(t_rtv *rtv, t_ray *ray)
{
	double	t;
	int		i;

	i = 0;
	rtv->comp->type = 0;
	rtv->comp->t[0] = planes_intersection(rtv, ray);
	rtv->comp->t[1] = spheres_intersection(rtv, ray);
	rtv->comp->t[2] = cylinders_intersection(rtv, ray);
	rtv->comp->t[3] = cones_intersection(rtv, ray);
	t = fmax(fmax(rtv->comp->t[0], rtv->comp->t[1]),
			fmax(rtv->comp->t[2], rtv->comp->t[3]));
	rtv->cam->ray.t = 0;
	while (i < 4)
	{
		if (rtv->comp->t[i] <= t && rtv->comp->t[i] != 0)
		{
			t = rtv->comp->t[i];
			rtv->comp->type = i;
		}
		i++;
	}
	ray->t = t;
	return (t);
}

void	composed_entry(t_rtv *rtv)
{
	int		x;
	int		y;
	t_vec3	pixel_coor;

	composed_params(rtv);
	cam_check(rtv);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel_coor.x = (2 * (x + 0.5) / WIDTH - 1) * ASPECT * tan(FOV / 2);
			pixel_coor.y = (1 - 2 * (y + 0.5) / HEIGHT) * tan(FOV / 2);
			pixel_coor.z = rtv->cam->start.z - 1;
			rtv->cam->ray.dir = vec3_norm(vec3_sub(pixel_coor,
												rtv->cam->start));
			rtv->cam->ray.dir = m_apply(rtv->mxs.rot_cam, rtv->cam->ray.dir);
			rtv->cam->ray.dir = m_apply(rtv->mxs.rot_dir, rtv->cam->ray.dir);
			if (cp_intersection_find(rtv, &rtv->cam->ray) != 0.0)
				ipp_fill(rtv, x, y, color_count(rtv,
											*obj_color(rtv, &rtv->cam->ray)));
		}
	}
}
