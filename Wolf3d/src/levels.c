#include "../includes/wolf3d.h"

void	starting_parameters_1(t_env *env)
{
	env->name = ft_strdup("maps/level_1");
	env->player.pos = create_vec(3, 3);
	env->player.dir = create_vec(0, 1);
	env->player.points = -42;
	env->cast.plane = create_vec(1, 0);
	env->cast.map = create_i_vec(0, 0);
	env->cast.step = create_i_vec(0, 0);
	env->cast.x_aim = WIDTH / 2;
	env->level = 1;
}

void	starting_parameters_2(t_env *env)
{
	env->name = ft_strdup("maps/level_2");
	env->player.pos = create_vec(4, 4);
	env->player.dir = create_vec(0, 1);
	env->player.points = -42;
	env->cast.plane = create_vec(1, 0);
	env->cast.map = create_i_vec(0, 0);
	env->cast.step = create_i_vec(0, 0);
	env->cast.x_aim = WIDTH / 2;
	env->level = 2;
}

void	prepare_level(t_env *env, int level)
{
	int i;

	i = 0;
	if (level == 1)
	{
		starting_parameters_1(env);
		read_map(env);
		free(env->name);
		env->name = 0;
	}
	if (level == 2)
	{
		starting_parameters_2(env);
		while (i <= env->map.y_dim)
		{
			free(env->map.map[i]);
			++i;
		}
		free(env->map.map);
		read_map(env);
		free(env->name);
		env->name = 0;
		define_sprites_2(env);
	}
	if (level == 3)
		end_game(env);
}
