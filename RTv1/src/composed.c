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
		plane_vectors(rtv, ray);
		return (&rtv->plane->color);
	}
	if (rtv->comp->type == 1)
	{
		sphere_vectors(rtv, ray);
		return (&rtv->sphere->color);
	}
	if (rtv->comp->type == 2)
	{
		cylinder_vectors(rtv, ray);
		return (&rtv->cyl->color);
	}
	if (rtv->comp->type == 3)
	{
		cone_vectors(rtv, ray);
		return (&rtv->cone->color);
	}
	return (0);
}

double	shadowed(t_rtv *rtv, int i)
{
	double	t;

	rtv->light->sh_ray[i].pos = vec3_add(rtv->cam->ray.v,
										vec3_mult(rtv->cam->ray.n, 0.0001));
	rtv->light->sh_ray[i].dir = rtv->cam->ray.l[i];
	rtv->light->sh_t[0] = p_intersection_find(rtv, &rtv->light->sh_ray[i]);
	rtv->light->sh_t[1] = s_intersection_find(rtv, &rtv->light->sh_ray[i]);
	rtv->light->sh_t[2] = cl_intersection_find(rtv, &rtv->light->sh_ray[i]);
	rtv->light->sh_t[3] = cn_intersection_find(rtv, &rtv->light->sh_ray[i]);
	t = fmax(fmax(rtv->light->sh_t[0], rtv->light->sh_t[1]),
			fmax(rtv->light->sh_t[2], rtv->light->sh_t[3]));
	return (t);
}

void	shadow_count(t_rtv *rtv, double *r, double *g, double *b)
{
	int i;

	i = 0;
	while (i < LIGHT_SOURCES)
	{
		if (rtv->type == 4 && shadowed(rtv, i) != 0.0)
		{
			*r *= (1 - AMBIENT_R);
			*g *= (1 - AMBIENT_G);
			*b *= (1 - AMBIENT_B);
		}
		i++;
	}
}

double	cp_intersection_find(t_rtv *rtv)
{
	double	t;
	int		i;

	i = 0;
	rtv->comp->type = 0;
	rtv->comp->t[0] = p_intersection_find(rtv, &rtv->cam->ray);
	rtv->comp->t[1] = s_intersection_find(rtv, &rtv->cam->ray);
	rtv->comp->t[2] = cl_intersection_find(rtv, &rtv->cam->ray);
	rtv->comp->t[3] = cn_intersection_find(rtv, &rtv->cam->ray);
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
	rtv->cam->ray.t = t;
	return (t);
}

void	composed_entry(t_rtv *rtv)
{
	int		x;
	int		y;
	t_vec3	pixel_coor;

	composed_params(rtv);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_coor.x = (2 * (x + 0.5) / WIDTH - 1) * ASPECT * tan(FOV / 2);
			pixel_coor.y = (1 - 2 * (y + 0.5) / HEIGHT) * tan(FOV / 2);
			pixel_coor.z = rtv->cam->pos.z - 1;
			rtv->cam->ray.dir = vec3_norm(vec3_sub(pixel_coor,
												rtv->cam->ray.pos));
			if (cp_intersection_find(rtv) != 0.0)
				mlx_pixel_put(rtv->mlx->mlx, rtv->mlx->window, x, y,
							color_count(rtv, *obj_color(rtv, &rtv->cam->ray)));
			x++;
		}
		y++;
	}
}
