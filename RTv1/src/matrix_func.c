/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:59:33 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/29 10:59:34 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix	m_mult(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	int			k;
	double		sum;
	t_matrix	m3;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			sum = 0;
			k = 0;
			while (k++ < 4)
				sum += m1.m[i][k - 1] * m2.m[k - 1][j];
			m3.m[i][j] = sum;
			j++;
		}
		i++;
	}
	return (m3);
}

t_matrix	x_rot(double angle)
{
	t_matrix	x_rot;

	x_rot.m[0][0] = 1;
	x_rot.m[0][1] = 0;
	x_rot.m[0][2] = 0;
	x_rot.m[0][3] = 0;
	x_rot.m[1][0] = 0;
	x_rot.m[1][1] = cos(angle);
	x_rot.m[1][2] = -sin(angle);
	x_rot.m[1][3] = 0;
	x_rot.m[2][0] = 0;
	x_rot.m[2][1] = sin(angle);
	x_rot.m[2][2] = cos(angle);
	x_rot.m[2][3] = 0;
	x_rot.m[3][0] = 0;
	x_rot.m[3][1] = 0;
	x_rot.m[3][2] = 0;
	x_rot.m[3][3] = 1;
	return (x_rot);
}

t_matrix	y_rot(double angle)
{
	t_matrix y_rot;

	y_rot.m[0][0] = cos(angle);
	y_rot.m[0][1] = 0;
	y_rot.m[0][2] = -sin(angle);
	y_rot.m[0][3] = 0;
	y_rot.m[1][0] = 0;
	y_rot.m[1][1] = 1;
	y_rot.m[1][2] = 0;
	y_rot.m[1][3] = 0;
	y_rot.m[2][0] = sin(angle);
	y_rot.m[2][1] = 0;
	y_rot.m[2][2] = cos(angle);
	y_rot.m[2][3] = 0;
	y_rot.m[3][0] = 0;
	y_rot.m[3][1] = 0;
	y_rot.m[3][2] = 0;
	y_rot.m[3][3] = 1;
	return (y_rot);
}

t_matrix	z_rot(double angle)
{
	t_matrix z_rot;

	z_rot.m[0][0] = cos(angle);
	z_rot.m[0][1] = -sin(angle);
	z_rot.m[0][2] = 0;
	z_rot.m[0][3] = 0;
	z_rot.m[1][0] = sin(angle);
	z_rot.m[1][1] = cos(angle);
	z_rot.m[1][2] = 0;
	z_rot.m[1][3] = 0;
	z_rot.m[2][0] = 0;
	z_rot.m[2][1] = 0;
	z_rot.m[2][2] = 1;
	z_rot.m[2][3] = 0;
	z_rot.m[3][0] = 0;
	z_rot.m[3][1] = 0;
	z_rot.m[3][2] = 0;
	z_rot.m[3][3] = 1;
	return (z_rot);
}

t_vec3		m_apply(t_matrix matrix, t_vec3 vec)
{
	t_vec3	result;

	result.x = matrix.m[0][0] * vec.x + matrix.m[0][1] * vec.y +
			matrix.m[0][2] * vec.z + matrix.m[0][3];
	result.y = matrix.m[1][0] * vec.x + matrix.m[1][1] * vec.y +
			matrix.m[1][2] * vec.z + matrix.m[1][3];
	result.z = matrix.m[2][0] * vec.x + matrix.m[2][1] * vec.y +
			matrix.m[2][2] * vec.z + matrix.m[2][3];
	return (result);
}
