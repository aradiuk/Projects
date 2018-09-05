#include "../includes/wolf3d.h"

void	ipp_fill(t_env *env, int color)
{
	t_cast *cast;

	cast = &env->cast;
	*((int *)(env->img.ipp + cast->it.x * env->img.bpp / 8 + cast->it.y *
			env->img.sline)) = color;
}

void	vertical_line(t_env *env)
{
	t_cast	*cast;
	int		tx_num;

	cast = &env->cast;
	cast->it.y = cast->draw_start;
	while (cast->it.y <= cast->draw_end)
	{
		tx_num = env->map.map[cast->map.x][cast->map.y] - '1';
		if (env->cast.side == 0)
			double wallx = env->cast.ray.pos.y + env->cast
					.p_wall_dist*env->cast.ray.dir.y;
		else
			double wallx = env->cast.ray.pos.x + env->cast
					.p_wall_dist*env->cast.ray.dir.x;
		wallx -= floor(wallx);
		int texx = (int)(wallx*64.0);
		if (env->cast.side == 0 && env->cast.ray.dir.x > 0)
			texx = 64 - texx - 1;
		if (env->cast.side == 1 && env->cast.ray.dir.y > 0)
			texx = 64 - texx - 1;
		int d = cast->it.y * 256 - HEIGHT * 128 + cast->line_height * 128;
		int texy = ((d * 64) / cast->line_height) / 256;
		
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