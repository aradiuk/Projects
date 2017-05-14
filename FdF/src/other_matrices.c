/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_matrices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:13:57 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/16 14:14:02 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_matrix	*m_tr_declare(double x, double y, double z)
{
	t_matrix *translation;

	translation = (t_matrix *)malloc(sizeof(t_matrix));
	translation->m[0][0] = 1;
	translation->m[0][1] = 0;
	translation->m[0][2] = 0;
	translation->m[0][3] = x;
	translation->m[1][0] = 0;
	translation->m[1][1] = 1;
	translation->m[1][2] = 0;
	translation->m[1][3] = y;
	translation->m[2][0] = 0;
	translation->m[2][1] = 0;
	translation->m[2][2] = 1;
	translation->m[2][3] = z;
	translation->m[3][0] = 0;
	translation->m[3][1] = 0;
	translation->m[3][2] = 0;
	translation->m[3][3] = 1;
	return (translation);
}

t_matrix	*x_rot_declare(double angle)
{
	t_matrix	*x_rot;

	x_rot = (t_matrix *)malloc(sizeof(t_matrix));
	x_rot->m[0][0] = 1;
	x_rot->m[0][1] = 0;
	x_rot->m[0][2] = 0;
	x_rot->m[0][3] = 0;
	x_rot->m[1][0] = 0;
	x_rot->m[1][1] = cos(angle);
	x_rot->m[1][2] = -sin(angle);
	x_rot->m[1][3] = 0;
	x_rot->m[2][0] = 0;
	x_rot->m[2][1] = sin(angle);
	x_rot->m[2][2] = cos(angle);
	x_rot->m[2][3] = 0;
	x_rot->m[3][0] = 0;
	x_rot->m[3][1] = 0;
	x_rot->m[3][2] = 0;
	x_rot->m[3][3] = 1;
	return (x_rot);
}

t_matrix	*y_rot_declare(double angle)
{
	t_matrix *y_rot;

	y_rot = (t_matrix *)malloc(sizeof(t_matrix));
	y_rot->m[0][0] = cos(angle);
	y_rot->m[0][1] = 0;
	y_rot->m[0][2] = sin(angle);
	y_rot->m[0][3] = 0;
	y_rot->m[1][0] = 0;
	y_rot->m[1][1] = 1;
	y_rot->m[1][2] = 0;
	y_rot->m[1][3] = 0;
	y_rot->m[2][0] = -sin(angle);
	y_rot->m[2][1] = 0;
	y_rot->m[2][2] = cos(angle);
	y_rot->m[2][3] = 0;
	y_rot->m[3][0] = 0;
	y_rot->m[3][1] = 0;
	y_rot->m[3][2] = 0;
	y_rot->m[3][3] = 1;
	return (y_rot);
}

t_matrix	*z_rot_declare(double angle)
{
	t_matrix *z_rot;

	z_rot = (t_matrix *)malloc(sizeof(t_matrix));
	z_rot->m[0][0] = cos(angle);
	z_rot->m[0][1] = -sin(angle);
	z_rot->m[0][2] = 0;
	z_rot->m[0][3] = 0;
	z_rot->m[1][0] = sin(angle);
	z_rot->m[1][1] = cos(angle);
	z_rot->m[1][2] = 0;
	z_rot->m[1][3] = 0;
	z_rot->m[2][0] = 0;
	z_rot->m[2][1] = 0;
	z_rot->m[2][2] = 1;
	z_rot->m[2][3] = 0;
	z_rot->m[3][0] = 0;
	z_rot->m[3][1] = 0;
	z_rot->m[3][2] = 0;
	z_rot->m[3][3] = 1;
	return (z_rot);
}

t_matrix	*m_scale_declare(double x, double y, double z)
{
	t_matrix	*scale;

	scale = (t_matrix *)malloc(sizeof(t_matrix));
	scale->m[0][0] = x;
	scale->m[0][1] = 0;
	scale->m[0][2] = 0;
	scale->m[0][3] = 0;
	scale->m[1][0] = 0;
	scale->m[1][1] = y;
	scale->m[1][2] = 0;
	scale->m[1][3] = 0;
	scale->m[2][0] = 0;
	scale->m[2][1] = 0;
	scale->m[2][2] = z;
	scale->m[2][3] = 0;
	scale->m[3][0] = 0;
	scale->m[3][1] = 0;
	scale->m[3][2] = 0;
	scale->m[3][3] = 1;
	return (scale);
}
