/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:52:42 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/10 12:52:44 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3	prot;

	prot.x = x;
	prot.y = y;
	prot.z = z;
	return (prot);
}

t_vec3	vec3_norm(t_vec3 vector)
{
	double	length;

	length = sqrt(vector.x * vector.x + vector.y * vector.y +
												vector.z * vector.z);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return (vector);
}

t_vec3	vec3_invert(t_vec3 vector)
{
	vector.x = -vector.x;
	vector.y = -vector.y;
	vector.z = -vector.z;
	return (vector);
}

double	vec3_dp(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

void	null_rgb(t_color *color)
{
	color->r = color->rgb.x * AMBIENT_R;
	color->g = color->rgb.y * AMBIENT_G;
	color->b = color->rgb.z * AMBIENT_B;
}
