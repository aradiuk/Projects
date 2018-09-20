#include "../includes/wolf3d.h"

void    fill_ipp(t_env *env, int img_coor, int tx_coor, int tx_num)
{
    char	*img_ipp;

    img_ipp = env->img.ipp;
    img_ipp[img_coor] = env->tx[tx_num].ipp[tx_coor];
    img_ipp[img_coor + 1] = env->tx[tx_num].ipp[tx_coor + 1];
    img_ipp[img_coor + 2] = env->tx[tx_num].ipp[tx_coor + 2];
}

void    fill_middle(t_env *env, int tx_coor)
{
    int     img_coor;
    char	*img_ipp;
    t_cast	*cast;

	cast = &env->cast;
    img_ipp = env->img.ipp;
    img_coor = cast->it.x * env->img.bpp / 8 + cast->it.y * env->img.sline;
    fill_ipp(env, img_coor, tx_coor, cast->tx_num);

    if (env->cast.side == 1)
    {
		img_ipp[img_coor] = (env->img.ipp[img_coor] >> 1) & 8355711;
		img_ipp[img_coor + 1] = (env->img.ipp[img_coor + 1] >> 1) & 8355711;
		img_ipp[img_coor + 2] = (env->img.ipp[img_coor + 2] >> 1) & 8355711;
    }
}

void	find_texture(t_env *env)
{
	t_cast	*cast;

	cast = &env->cast;
	cast->tx_num = env->map.map[cast->map.x][cast->map.y] - '1';
	if (cast->tx_num < 0)
		error("something strange happened");
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
	int		tx_coor;

	cast = &env->cast;
	cast->it.y = cast->draw_start;
	find_texture(env);
	while (cast->it.y <= cast->draw_end)
	{
		d = cast->it.y * 256 - HEIGHT * 128 + cast->line_height * 128;
		cast->tx_y = ((d * env->tx[cast->tx_num].height) / cast->line_height)
														/ 256;
		tx_coor = (env->tx[cast->tx_num].sline * cast->tx_y + cast->tx_x *
				env->tx[cast->tx_num].bpp / 8);
        fill_middle(env, tx_coor);
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
		env->z_buf[env->cast.it.x] = env->cast.p_wall_dist;
		fill_sky_and_floor(env);
		++env->cast.it.x;
	}
	sprites(env);
}
