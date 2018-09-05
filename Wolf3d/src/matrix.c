#include "../includes/wolf3d.h"

t_mat	init_matrix(double angle)
{
	t_mat	mat;

	mat.m[0][0] = cos(angle);
	mat.m[0][1] = -sin(angle);
	mat.m[1][0] = sin(angle);
	mat.m[1][1] = cos(angle);

	return (mat);
}

t_vec	m_apply(t_vec vec, double angle)
{
	t_mat	mat;
	t_vec	res;

	mat = init_matrix(angle);
	res.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y;
	res.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y;

	return (res);
}

t_vec	m_perp_apply(t_vec vec, int dir)
{
	t_mat	mat;
	t_vec	res;

	if (dir == 0)
		return (create_vec(0, 0));

	if (dir == -1)
	{
		mat = init_matrix(90 * M_PI / 180.);
		res.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y;
		res.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y;
	}
	else if (dir == 1)
	{
		mat = init_matrix(-90 * M_PI / 180.);
		res.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y;
		res.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y;
	}
	return (res);
}