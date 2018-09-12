#include "../includes/wolf3d.h"

void    create_the_environment(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3d");
	prepare_textures(env);
    create_image(env);
	mlx_hook(env->win, 17, 1L << 17, cross_exit, env);
	mlx_hook(env->win, 6, 1L << 6, mouse_rotation, env);
	mlx_hook(env->win, 2, 3, keyhooks, env);
	mlx_loop(env->mlx);
}

void	create_image(t_env *env)
{
	env->img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->img.ipp = mlx_get_data_addr(env->img.img, &env->img.bpp,
							&env->img.sline, &env->img.endn);
	fill_image(env);
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
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

	int i = -1;
	int j;
	while (++i < env->map.y_dim)
	{
		j = -1;
		while (++j < env->map.x_dim)
			printf("%c ", env->map.map[j][i]);
		printf("\n");
	}
	printf("\n");

}