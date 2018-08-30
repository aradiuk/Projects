#include "../includes/wolf3d.h"

void	raycasting(t_env *env)
{
	int i = 0;
	while (i < 100)
	mlx_pixel_put(env->mlx, env->win, 100 + i , 200 + i++, 16000);
	(void)env;
}