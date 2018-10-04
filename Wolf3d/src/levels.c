#include "../includes/wolf3d.h"

void	starting_parameters_1(t_env *env)
{
	env->name = ft_strdup("maps/level_1");
	env->player.pos = create_vec(3, 3);
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
	env->player.pos = create_vec(3, 3);
	env->player.dir = create_vec(0, 1);
	env->player.points = 0;
	env->cast.plane = create_vec(1, 0);
	env->cast.map = create_i_vec(0, 0);
	env->cast.step = create_i_vec(0, 0);
	env->cast.x_aim = WIDTH / 2;
	env->level = 2;
}

void	define_sprites(t_env *env)
{
	env->spr[0] = define_sprite(2, 4, 0);
	env->spr[1] = define_sprite(2, 5, 0);
	env->spr[2] = define_sprite(2, 6, 0);
	env->spr[3] = define_sprite(5, 6, 1);
	env->spr[4] = define_sprite(5, 4, 1);
	env->spr[5] = define_sprite(5, 5, TWO_P);
	env->spr[6] = define_sprite(10, 2, TEN_P);
	env->spr[7] = define_sprite(10, 8, TEN_P);
	env->spr[8] = define_sprite(14, 2, TEN_P);
	env->spr[9] = define_sprite(14, 8, TEN_P);
	env->spr[10] = define_sprite(18, 4, 1);
	env->spr[11] = define_sprite(18, 6, 1);
	env->spr[12] = define_sprite(18, 5, 4);
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
