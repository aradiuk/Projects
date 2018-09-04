#include "../includes/wolf3d.h"

void	ipp_fill(t_env *env, int color)
{
	t_cast *cast;

	cast = &env->cast;
	*((int *)(env->img.ipp + cast->it.x * env->img.bpp / 8 + cast->it.y *
			env->img.sizeline)) = color;
}

void	vertical_line(t_env *env)
{
	t_cast	*cast;
	int		tx_num;

	cast = &env->cast;
	cast->it.y = cast->draw_start;
	while (cast->it.y <= cast->draw_end)
	{
		tx_num = env->map.map[cast->map.x][cast->map.y] - '0';
		if (tx_num == 1)
			ipp_fill(env, BLUE);
		else if (tx_num == 2)
			ipp_fill(env, GREEN);
		else if (tx_num == 3)
			ipp_fill(env, RED);
		else
			ipp_fill(env, 1048575);
		++cast->it.y;
	}
}

void	fill_image(t_env *env)
{
	env->cast.it.x = 0;
	while (env->cast.it.x < WIDTH)
	{
		init_geom(env);
		calculate_step(env);
		check_hit(env);
		calculate_height(env);
		vertical_line(env);
		++env->cast.it.x;
	}
}