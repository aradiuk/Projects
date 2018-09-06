#include "../includes/wolf3d.h"

void	ipp_fill(t_env *env, int color)
{
	t_cast *cast;

	cast = &env->cast;
	*((int *)(env->img.ipp + cast->it.x * env->img.bpp / 8 + cast->it.y *
			env->img.sline)) = color;
}

void	find_texture(t_env *env)
{
	t_cast	*cast;

	cast = &env->cast;
	cast->tx_num = env->map.map[cast->map.x][cast->map.y] - '1';
	if (cast->tx_num > TEXTURES)
		error("too high texture number");
	if (cast->side == 0)
		cast->wall_x = env->player.pos.y + cast->p_wall_dist * cast->ray
				.dir.y;
	else
		cast->wall_x = env->player.pos.x + cast->p_wall_dist * cast->ray
				.dir.x;
	cast->wall_x -= floor(cast->wall_x);
	cast->tx_x = (int)(cast->wall_x * (double)env->tx[cast->tx_num].width);
	if ((cast->side == 0 && cast->ray.dir.x > 0) ||
		(cast->side == 1 && cast->ray.dir.y < 0))
		cast->tx_x = env->tx[cast->tx_num].width - cast->tx_x - 1;
}

void	vertical_line(t_env *env)
{
	t_cast	*cast;
	int		d;
	int		color;
	int		tx_coor;
	char	*tx_ipp;

	cast = &env->cast;
	cast->it.y = cast->draw_start;
	find_texture(env);
	tx_ipp = env->tx[cast->tx_num].ipp;
	while (cast->it.y <= cast->draw_end)
	{
		d = cast->it.y * 256 - HEIGHT * 128 + cast->line_height * 128;
		cast->tx_y = ((d * env->tx[cast->tx_num].height) / cast->line_height)
														/ 256;
		tx_coor = (int)(env->tx[cast->tx_num].sline * cast->tx_y + cast->tx_x *
				env->tx[cast->tx_num].bpp / 8);
		color = tx_ipp[tx_coor] + (tx_ipp[tx_coor + 1] << 8) +
				(tx_ipp[tx_coor + 2] << 16);
		if (cast->side == 1)
			color = (color >> 1) & 8355711;
		ipp_fill(env, color);
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