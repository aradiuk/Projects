#include "../includes/wolf3d.h"

void	error(char *str)
{
	printf("error: %s\n", str);
	exit(-1);
}

void	define_sprites(t_env *env)
{
	env->spr[0] = define_sprite(4, 3, 0);
	env->spr[1] = define_sprite(3, 3, 1);
	env->spr[2] = define_sprite(2, 3, 1);
	env->spr[3] = define_sprite(1, 3, 1);
	env->spr[4] = define_sprite(0, 3, 1);

}

void	starting_parameters(t_env *env)
{
	env->name = ft_strdup("maps/level_1");
	env->player.pos = create_vec(4, 4);
	env->player.dir = create_vec(0, 1);
	env->cast.plane = create_vec(1, 0);
	env->cast.map = create_i_vec(0, 0);
	env->cast.step = create_i_vec(0, 0);
	env->cast.x_aim = WIDTH / 2;
}

int		main(int argc, char **argv)
{
	t_env env;

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (-1);
	}
	starting_parameters(&env);
	read_map(&env);
	create_the_environment(&env);
	return (0);
}
