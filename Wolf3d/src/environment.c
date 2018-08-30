#include "../includes/wolf3d.h"

int		expose(t_env *env)
{
	create_image(env);
	return (0);
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