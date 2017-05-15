/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 17:34:54 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/24 15:02:17 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		boundaries(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	fdf->mxs->bounds[5] = 0;
	fdf->mxs->bounds[4] = 0;
	while (i < fdf->map->lines)
	{
		j = 0;
		while (j < fdf->map->symbols)
		{
			if (fdf->map->coord[i][j].z > fdf->mxs->bounds[4])
				fdf->mxs->bounds[4] = fdf->map->coord[i][j].z;
			if (fdf->map->coord[i][j].z < fdf->mxs->bounds[5])
				fdf->mxs->bounds[5] = fdf->map->coord[i][j].z;
			j++;
		}
		i++;
	}
	fdf->mxs->bounds[0] = 0;
	fdf->mxs->bounds[1] = fdf->map->symbols;
	fdf->mxs->bounds[2] = 0;
	fdf->mxs->bounds[3] = fdf->map->lines;
}

void		m_vp_declare(t_fdf *fdf)
{
	fdf->mxs->m_vp = (t_matrix *)malloc(sizeof(t_matrix));
	fdf->mxs->m_vp->m[0][0] = WIDTH / 2.;
	fdf->mxs->m_vp->m[0][1] = 0;
	fdf->mxs->m_vp->m[0][2] = 0;
	fdf->mxs->m_vp->m[0][3] = (WIDTH - 1) / 2.;
	fdf->mxs->m_vp->m[1][0] = 0;
	fdf->mxs->m_vp->m[1][1] = HEIGHT / 2.;
	fdf->mxs->m_vp->m[1][2] = 0;
	fdf->mxs->m_vp->m[1][3] = (HEIGHT - 1) / 2.;
	fdf->mxs->m_vp->m[2][0] = 0;
	fdf->mxs->m_vp->m[2][1] = 0;
	fdf->mxs->m_vp->m[2][2] = 1;
	fdf->mxs->m_vp->m[2][3] = 0;
	fdf->mxs->m_vp->m[3][0] = 0;
	fdf->mxs->m_vp->m[3][1] = 0;
	fdf->mxs->m_vp->m[3][2] = 0;
	fdf->mxs->m_vp->m[3][3] = 1;
	m_or_declare(fdf);
}

void		m_or_declare(t_fdf *fdf)
{
	boundaries(fdf);
	fdf->mxs->m_or = (t_matrix *)malloc(sizeof(t_matrix));
	fdf->mxs->m_or->m[0][0] = 2. / fdf->mxs->bounds[1];
	fdf->mxs->m_or->m[0][1] = 0;
	fdf->mxs->m_or->m[0][2] = 0;
	fdf->mxs->m_or->m[0][3] = -1;
	fdf->mxs->m_or->m[1][0] = 0;
	fdf->mxs->m_or->m[1][1] = 2. / fdf->mxs->bounds[3];
	fdf->mxs->m_or->m[1][2] = 0;
	fdf->mxs->m_or->m[1][3] = -1;
	fdf->mxs->m_or->m[2][0] = 0;
	fdf->mxs->m_or->m[2][1] = 0;
	fdf->mxs->m_or->m[2][2] = (2. / (fdf->mxs->bounds[4] -
													fdf->mxs->bounds[5] + 1));
	fdf->mxs->m_or->m[2][3] = -((fdf->mxs->bounds[5] + fdf->mxs->bounds[4]) /
							(fdf->mxs->bounds[4] - fdf->mxs->bounds[5] + 1));
	fdf->mxs->m_or->m[3][0] = 0;
	fdf->mxs->m_or->m[3][1] = 0;
	fdf->mxs->m_or->m[3][2] = 0;
	fdf->mxs->m_or->m[3][3] = 1;
}

t_matrix	*mxs_mult(t_matrix *m1, t_matrix *m2)
{
	int			i;
	int			j;
	int			k;
	double		sum;
	t_matrix	*m3;

	i = 0;
	m3 = (t_matrix *)malloc(sizeof(t_matrix));
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			sum = 0;
			k = 0;
			while (k++ < 4)
				sum += m1->m[i][k - 1] * m2->m[k - 1][j];
			m3->m[i][j] = sum;
			j++;
		}
		i++;
	}
	return (m3);
}

t_matrix	*matrices(t_fdf *fdf)
{
	t_matrix	*m_vp_or;
	t_matrix	*rot_xy;
	t_matrix	*rot_xyz;
	t_matrix	*unskaled;

	fdf->mxs = (t_matrices *)malloc(sizeof(t_matrices));
	m_vp_declare(fdf);
	fdf->mxs->m_tr = m_tr_declare(fdf->map->symbols / 2 + 0.5,
					fdf->map->lines / 2 + 0.5, (fabs(fdf->mxs->bounds[4]) +
					fabs(fdf->mxs->bounds[5])) / 2);
	fdf->mxs->x_rot = x_rot_declare(X_ANGLE);
	fdf->mxs->y_rot = y_rot_declare(Y_ANGLE);
	fdf->mxs->z_rot = z_rot_declare(Z_ANGLE);
	m_vp_or = mxs_mult(fdf->mxs->m_vp, fdf->mxs->m_or);
	fdf->mxs->m_vp_or_tr = mxs_mult(m_vp_or, fdf->mxs->m_tr);
	free(m_vp_or);
	rot_xy = mxs_mult(fdf->mxs->x_rot, fdf->mxs->y_rot);
	rot_xyz = mxs_mult(rot_xy, fdf->mxs->z_rot);
	free(rot_xy);
	unskaled = mxs_mult(fdf->mxs->m_vp_or_tr, rot_xyz);
	fdf->mxs->scale = m_scale_declare(SCALE, SCALE, SCALE);
	fdf->mxs->m_final = mxs_mult(unskaled, fdf->mxs->scale);
	free(unskaled);
	free(rot_xyz);
	return (fdf->mxs->m_final);
}
