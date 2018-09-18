#include "../includes/wolf3d.h"

void    create_the_environment(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3d");
	prepare_textures(env);
	define_sprites(env);
	prepare_sprites(env);
	create_image(env);
	mlx_hook(env->win, 17, 1L << 17, cross_exit, env);
	mlx_hook(env->win, 6, 1L << 6, mouse_rotation, env);
	mlx_hook(env->win, 2, 3, keyhooks, env);
	mlx_loop(env->mlx);
}

void	create_image(t_env *env)
{
	char	*points;
	char	*out;

	env->img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->img.ipp = mlx_get_data_addr(env->img.img, &env->img.bpp,
							&env->img.sline, &env->img.endn);
	fill_image(env);
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	points = ft_itoa(env->player.points);
	out = ft_strjoin("Guess how many you should have: ", points);
	mlx_string_put(env->mlx, env->win, WIDTH / 2. - 60, 15, 0xFFFFFF, out);
	free(points);
	free(out);
	mlx_destroy_image(env->mlx, env->img.img);
}

void	open_door(t_env *env)
{
	t_entity	*p;
	char 		**m;

	p = &env->player;
	m = env->map.map;
	if (m[(int)p->pos.x][(int)p->pos.y] == DOOR + '1' ||
		m[(int)p->pos.x][(int)p->pos.y] == '+')
		return ;
	if (m[(int)(p->pos.x + p->dir.x)][(int)(p->pos.y + p->dir.y)] == DOOR + '1')
		m[(int)(p->pos.x + p->dir.x)][(int)(p->pos.y + p->dir.y)] = '+';
	else if (m[(int)(p->pos.x + p->dir.x)][(int)(p->pos.y + p->dir.y)] == '+')
		m[(int)(p->pos.x + p->dir.x)][(int)(p->pos.y + p->dir.y)] = DOOR + '1';
	else if (m[(int)(p->pos.x + p->dir.x)][(int)(p->pos.y + p->dir.y)] ==
																SC_DOOR + '1')
		m[(int)(p->pos.x + p->dir.x)][(int)(p->pos.y + p->dir.y)] = '*';
}

void	remove_object(t_env *env, int i)
{
	if (env->spr[i].tx == TWO_P)
		env->player.points -= 2;
	else if (env->spr[i].tx == TEN_P)
		env->player.points -= 10;
	if (env->player.points < -42)
		env->player.points = -42;
	env->spr[i].pos.x = -1000;
	env->spr[i].pos.y = -1000;
}