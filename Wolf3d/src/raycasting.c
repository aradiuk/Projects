#include "../includes/wolf3d.h"

void	init_geom(t_env *env)
{
	t_cast	*cast;
	double	cam_x;

	cast = &env->cast;
	cam_x = 2 * cast->it.x / (double)WIDTH - 1;

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
		cast->side_dist.x = (env->player.pos.x - cast->map.x) *
				cast->delta_dist.x;
	}
	else
	{
		cast->step.x = 1;
		cast->side_dist.x = (cast->map.x + 1.0 - env->player.pos.x) *
				cast->delta_dist.x;
	}
	if (cast->ray.dir.y < 0)
	{
		cast->step.y = -1;
		cast->side_dist.y = (env->player.pos.y - cast->map.y) *
				cast->delta_dist.y;
	}
	else
	{
		cast->step.y = 1;
		cast->side_dist.y = (cast->map.y + 1.0 - env->player.pos.y) *
							cast->delta_dist.y;
	}
}

void	check_hit(t_env *env)
{
	t_cast	*cast;

	cast = &env->cast;
	cast->hit = 0;
	while (cast->hit == 0)
	{
		if (cast->side_dist.x < cast->side_dist.y)
		{
			cast->side_dist.x += cast->delta_dist.x;
			cast->map.x += cast->step.x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist.y += cast->delta_dist.y;
			cast->map.y += cast->step.y;
			cast->side = 1;
		}
			//	Add boundaries check
		if (env->map.map[cast->map.x][cast->map.y] > '0')
			cast->hit = 1;
	}
}

void	calculate_height(t_env *env)
{	t_cast	*cast;

	cast = &env->cast;
	if (cast->side == 0)
		cast->p_wall_dist = (cast->map.x - env->player.pos.x + (1 -
				cast->step.x) / 2.) / cast->ray.dir.x;
	else
		cast->p_wall_dist = (cast->map.y - env->player.pos.y + (1 -
				cast->step.y) / 2.) / cast->ray.dir.y;

	cast->line_height = (int)(HEIGHT / cast->p_wall_dist);
	cast->draw_start = -cast->line_height / 2 + HEIGHT / 2;
	cast->draw_end = cast->line_height / 2 + HEIGHT / 2;
	if (cast->draw_start < 0)
		cast->draw_start = 0;
	if (cast->draw_end >= HEIGHT)
		cast->draw_end = HEIGHT - 1;
}


