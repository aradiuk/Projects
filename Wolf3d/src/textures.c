#include "../includes/wolf3d.h"

void	prepare_textures(t_env *env)
{
	t_texture *t;

	t = &env->tx[0];
	t[0].img = mlx_xpm_file_to_image(env->mlx, "textures/colorstone.xpm",
									&t[0].width, &t[0].height);
	t[0].ipp = mlx_get_data_addr(t[0].img, &t[0].bpp, &t[0].sline, &t[0].endn);
	t[1].img = mlx_xpm_file_to_image(env->mlx, "textures/bluestone.xpm",
									&t[1].width, &t[1].height);
	t[1].ipp = mlx_get_data_addr(t[1].img, &t[1].bpp, &t[1].sline, &t[1].endn);
	t[2].img = mlx_xpm_file_to_image(env->mlx, "textures/greystone.xpm",
									&t[2].width, &t[2].height);
	t[2].ipp = mlx_get_data_addr(t[2].img, &t[2].bpp, &t[2].sline, &t[2].endn);
	t[3].img = mlx_xpm_file_to_image(env->mlx, "textures/mossy.xpm",
									&t[3].width, &t[3].height);
	t[3].ipp = mlx_get_data_addr(t[3].img, &t[3].bpp, &t[3].sline, &t[3].endn);
	t[4].img = mlx_xpm_file_to_image(env->mlx, "textures/redbrick.xpm",
									&t[4].width, &t[4].height);
	t[4].ipp = mlx_get_data_addr(t[4].img, &t[4].bpp, &t[4].sline, &t[4].endn);
	t[5].img = mlx_xpm_file_to_image(env->mlx, "textures/wood.xpm",
									&t[5].width, &t[5].height);
	t[5].ipp = mlx_get_data_addr(t[5].img, &t[5].bpp, &t[5].sline, &t[5].endn);
	t[6].img = mlx_xpm_file_to_image(env->mlx, "textures/wood.xpm",
									&t[6].width, &t[6].height);
	t[6].ipp = mlx_get_data_addr(t[6].img, &t[6].bpp, &t[6].sline, &t[6].endn);
	t[7].img = mlx_xpm_file_to_image(env->mlx, "textures/redbrick.xpm",
									&t[7].width, &t[7].height);
	t[7].ipp = mlx_get_data_addr(t[7].img, &t[7].bpp, &t[7].sline, &t[7].endn);
	t[8].img = mlx_xpm_file_to_image(env->mlx, "textures/eagle.xpm",
									 &t[8].width, &t[8].height);
	t[8].ipp = mlx_get_data_addr(t[8].img, &t[8].bpp, &t[8].sline, &t[8].endn);
}

void    init_sky(t_env *env)
{
    t_cast  *cast;

    cast = &env->cast;
    if (cast->side == 0 && cast->ray.dir.x > 0)
    {
        cast->sky_wall.x = cast->map.x;
        cast->sky_wall.y = cast->map.y + cast->wall_x;
    }
    else if (cast->side == 0 && cast->ray.dir.x < 0)
    {
        cast->sky_wall.x = cast->map.x + 1.0;
        cast->sky_wall.y = cast->map.y + cast->wall_x;
    }
    else if (cast->side == 1 && cast->ray.dir.y > 0)
    {
        cast->sky_wall.x = cast->map.x + cast->wall_x;
        cast->sky_wall.y = cast->map.y;
    }
    else if (cast->side == 1 && cast->ray.dir.y < 0)
    {
        cast->sky_wall.x = cast->map.x + cast->wall_x;
        cast->sky_wall.y = cast->map.y + 1.0;
    }
}

void    fill_sky_and_floor(t_env *env)
{
    t_cast  *cast;
    double  weight;
    int     tx_coor;
    int     img_coor;
    int     y;

    cast = &env->cast;
    init_sky(env);
    if (cast->draw_end < 0)
        cast->draw_end = HEIGHT;
    y = cast->draw_end + 1;
    while (y < HEIGHT)
    {
        weight = HEIGHT / (2.0 * y - HEIGHT) / cast->p_wall_dist;
        cast->sky_curr.x = weight * cast->sky_wall.x + (1.0 - weight) *
                env->player.pos.x;
        cast->sky_curr.y = weight * cast->sky_wall.y + (1.0 - weight) *
                env->player.pos.y;
        cast->sky_tx.x = (int)(cast->sky_curr.x * env->tx[SKY].width ) %
                env->tx[SKY].width;
        cast->sky_tx.y = (int)(cast->sky_curr.y * env->tx[SKY].height ) %
                env->tx[SKY].height;
        img_coor = cast->it.x * env->img.bpp / 8 + y * env->img.sline;
        tx_coor = (env->tx[SKY].sline * cast->sky_tx.y +
                        cast->sky_tx.x * env->tx[SKY].bpp / 8);
        fill_ipp(env, img_coor, tx_coor, FLOOR);
        img_coor = cast->it.x * env->img.bpp / 8 + (HEIGHT - y) * env->img.sline;
        fill_ipp(env, img_coor, tx_coor, SKY);
        ++y;
    }
}

void	prepare_sprites(t_env *env)
{
	t_texture *t;

	t = &env->spr_tx[0];
	t[0].img = mlx_xpm_file_to_image(env->mlx, "textures/barrel.xpm",
													&t[0].width, &t[0].height);
	t[0].ipp = mlx_get_data_addr(t[0].img, &t[0].bpp, &t[0].sline, &t[0].endn);
	t[1].img = mlx_xpm_file_to_image(env->mlx, "textures/pillar.xpm",
													&t[1].width, &t[1].height);
	t[1].ipp = mlx_get_data_addr(t[1].img, &t[1].bpp, &t[1].sline, &t[1].endn);
}