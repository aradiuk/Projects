#include "../includes/wolf3d.h"

void	init_geom(t_env *env)
{
	t_cast	*cast;
	double	cam_x;

	cast = &env->cast;
	cam_x = 2 * env->x / (double)WIDTH - 1;

	cast->ray.pos.x = env->player.pos.x;
	cast->ray.pos.y = env->player.pos.y;
	cast->ray.dir.x = env->player.dir.x + cast->plane.x * cam_x;
	cast->ray.dir.y = env->player.dir.y + cast->plane.y * cam_x;
	cast->map.x = (int)env->player.pos.x;
	cast->map.y = (int)env->player.pos.y;
	cast->delta_dist.x = fabs(1 / cast->ray.dir.x);
	cast->delta_dist.y = fabs(1 / cast->ray.dir.y);
}

void	calculate_step(t_env *env)
{
	t_cast	*cast;

	cast = &env->cast;
	if (cast->ray.dir.x < 0)
	{
		cast->step.x = -1;
		cast->side_dist.x = (env->player.pos.x - cast->map.x) * cast->delta_dist.x;
	}
	else
	{
		cast->step.x = 1;
		cast->side_dist.x = (cast->map.x + 1.0 - env->player.pos.x) * cast->delta_dist.x;
	}
	if (cast->ray.dir.y < 0)
	{
		cast->step.y = -1;
		cast->side_dist.y = (env->player.pos.y - cast->map.y) * cast->delta_dist.y;
	}
	else
	{
		cast->step.y = 1;
		cast->side_dist.y = (cast->map.y + 1.0 - env->player.pos.y) *
							cast->delta_dist.y;
	}
}

int		raycast(t_env *env)
{
	t_cast	*cast;
	int hit;
	int side;

    hit = 0;
    cast = &env->cast;

	while (hit == 0)
	{
		if (cast->side_dist.x < cast->side_dist.y)
		{
			cast->side_dist.x += cast->delta_dist.x;
			cast->map.x += cast->step.x;
			side = 0;
		}
		else
		{
			cast->side_dist.y += cast->delta_dist.y;
			cast->map.y += cast->step.y;
			side = 1;
		}
		printf("x: %d, y: %d\n", cast->map.x, cast->map.y);
		if (env->map.map[cast->map.x][cast->map.y] > 0)
			hit = 1;
		return (0);
	}
	return (1073741822);
}
