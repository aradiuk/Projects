#include "../includes/wolf3d.h"

void	ipp_fill(t_env *env, int color)
{
	*((int *)(env->img.ipp + (int)env->x * env->img.bpp / 8 + (int)env->y *
			env->img.sizeline)) = color;
}

void	fill_image(t_env *env)
{
	env->y = -1;
	while (++env->y < HEIGHT)
	{
		env->x = -1;
		while (++env->x < WIDTH)
		{
			ipp_fill(env, raycast(env));
		}
	}
}