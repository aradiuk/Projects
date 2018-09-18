#include "../includes/wolf3d.h"

void	starting_parameters_1(t_env *env)
{
	env->name = ft_strdup("maps/level_1");
	env->player.pos = create_vec(4, 4);
	env->player.dir = create_vec(0, 1);
	env->player.points = -30;
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
	env->player.points = -30;
	env->cast.plane = create_vec(1, 0);
	env->cast.map = create_i_vec(0, 0);
	env->cast.step = create_i_vec(0, 0);
	env->cast.x_aim = WIDTH / 2;
	env->level = 2;
}

void	define_sprites(t_env *env)
{
	env->spr[0] = define_sprite(5.5, 5.5, 0);
	env->spr[1] = define_sprite(5, 5, 1);
	env->spr[2] = define_sprite(5, 7, 1);
	env->spr[3] = define_sprite(7, 5, 2);
	env->spr[4] = define_sprite(7, 7, 3);
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
	}
	if (level == 2)
	{
		starting_parameters_2(env);
		while (i < env->map.y_dim)
		{
			free(env->map.map[i]);
			++i;
		}
		read_map(env);
		free(env->name);
		define_sprites(env);
	}
	if (level == 3)
		end_game(env);
}

void	end_game(t_env *env)
{
	int i;

	i = 0;
	while (i < env->map.y_dim)
	{
		free(env->map.map[i]);
		++i;
	}
	mlx_destroy_window(env->mlx, env->win);
	exit(1);
}