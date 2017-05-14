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

double	p_intersection_find(t_rtv *rtv, t_ray *ray)
{
	t_vec3	cam_to_plane;
	double	contained;
	double	denom;

	denom = vec3_dp(rtv->plane->normal, ray->dir);
	cam_to_plane = vec3_sub(rtv->plane->pos, ray->pos);
	contained = vec3_dp(cam_to_plane, rtv->plane->normal);
	ray->t = contained / denom;
	if ((denom <= 0.000001 && denom >= -0.000001) || contained == 0 ||
																	ray->t < 0)
		return (0);
	if (rtv->type == 0)
		plane_vectors(rtv, ray);
	return (ray->t);
}

void	plane_entry(t_rtv *rtv)
{
	int		x;
	int		y;
	t_vec3	pixel_coor;

	plane_params(rtv);
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
			if (p_intersection_find(rtv, &rtv->cam->ray) != 0.0)
				mlx_pixel_put(rtv->mlx->mlx, rtv->mlx->window, x, y,
							color_count(rtv, rtv->plane->color));
			x++;
		}
		y++;
	}
}
