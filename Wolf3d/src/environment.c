#include "../includes/wolf3d.h"

int		expose(t_env *env)
{
	create_image(env);
	return (0);
}

void    create_the_environment(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3d");
	mlx_expose_hook(env->win, expose, env);
	mlx_hook(env->win, 17, 1L << 17, cross_exit, env);
	mlx_hook(env->win, 6, 1L << 6, mouse_rotation, env);
	mlx_hook(env->win, 2, 1L << 2, keyhooks, env);
	mlx_loop(env->mlx);
}

void	create_image(t_env *env)
{
	env->img.img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->data = mlx_get_data_addr(env->img.img, &env->img.bpp,
							&env->img.sizeline, &env->img.endian);
	raycasting(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	mlx_destroy_image(env->mlx, env->img.img);
}