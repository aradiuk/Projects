#include "../includes/wolf3d.h"

void	ipp_fill(t_env *env, int x, int y, int color)
{
	*((int *)(env->img.ipp + x * env->img.bpp / 8 +
			  y * env->img.sizeline)) = color;
}

int		raycast(t_env *env, int x, int y)
{
	t_cast	*cast = &env->cast;
	double	cam_x = 2 * x / (double)WIDTH - 1;
	cast->ray.dir.x = env->player.dir.x + cast->plane.x * cam_x;
	cast->ray.dir.y = env->player.dir.y + cast->plane.y * cam_x;

	int map_x = (int)env->player.pos.x;
	int map_y = (int)env->player.pos.y;

	cast->delta_dist.x = fabs(1 / cast->ray.dir.x);
	cast->delta_dist.y = fabs(1 / cast->ray.dir.y);

	int	step_x;
	int step_y;
	if (cast->ray.dir.x < 0)
	{
		step_x = -1;
		cast->side_dist.x = (env->player.pos.x - map_x) * cast->delta_dist.x;
	}
	else
	{
		step_x = 1;
		cast->side_dist.x = (map_x + 1.0 - env->player.pos.x) * cast->delta_dist.x;
	}
	if (cast->ray.dir.y < 0)
	{
		step_y = -1;
		cast->side_dist.y = (env->player.pos.y - map_y) * cast->delta_dist.y;
	}
	else
	{
		step_y = 1;
		cast->side_dist.y = (map_y + 1.0 - env->player.pos.y) *
				cast->delta_dist.y;
	}

	int hit = 0;
	int side;

	while (hit == 0)
	{
		if (cast->side_dist.x < cast->side_dist.y)
		{
			cast->side_dist.x += cast->delta_dist.x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			cast->side_dist.y += cast->delta_dist.y;
			map_y += step_y;
			side = 1;
		}
		printf("x: %d, y: %d\n", map_x, map_y);
		if (env->map.map[map_x][map_y] > 0)
			hit = 1;
		return (0);
	}
	return (1073741822);
}

void	fill_image(t_env *env)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ipp_fill(env, x, y, raycast(env, x, y));
		}
	}
}