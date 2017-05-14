#include "rtv1.h"

t_matrix	m_tr(t_vec3	vec)
{
	t_matrix	matrix;

	matrix.m[0][0] = 1;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = vec.x;
	matrix.m[1][0] = 0;
	matrix.m[1][1] = 1;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = vec.y;
	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;
	matrix.m[2][3] = vec.z;
	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = 0;
	matrix.m[3][3] = 1;
	return (matrix);
}

t_matrix	m_rot(t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_matrix	matrix;

	matrix.m[0][0] = u.x;
	matrix.m[0][1] = u.y;
	matrix.m[0][2] = u.z;
	matrix.m[0][3] = 0;
	matrix.m[1][0] = v.x;
	matrix.m[1][1] = v.y;
	matrix.m[1][2] = v.z;
	matrix.m[1][3] = 0;
	matrix.m[2][0] = w.x;
	matrix.m[2][1] = w.y;
	matrix.m[2][2] = w.z;
	matrix.m[2][3] = 0;
	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = 0;
	matrix.m[3][3] = 1;
	return (matrix);
}

void	m_print(t_matrix matrix)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
			printf("%f ", matrix.m[i][j++]);
		printf("\n");
		i++;
	}
}
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

t_vec3	m_apply(t_matrix matrix, t_vec3 vec)
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
void	matrices(t_rtv *rtv)
{
	rtv->mxs.tr = m_tr(vec3_invert(rtv->cam->pos));
	rtv->mxs.rot = m_rot(rtv->cam->u, rtv->cam->v, rtv->cam->w);
	rtv->mxs.multed = m_mult(rtv->mxs.rot, rtv->mxs.tr);
	m_print(rtv->mxs.multed);
}