#include "../includes/wolf3d.h"

void    error(char *str)
{
	printf("error: %s\n", str);
	exit(-1);
}

void    starting_parameters(t_env *env)
{
	env->name = ft_strdup("maps/level_1");
	env->player.pos = create_vec(3, 3);
	env->player.dir = create_vec(0, 1);
	env->cast.plane = create_vec(1, 0);
    env->cast.map = create_i_vec(0, 0);
    env->cast.step = create_i_vec(0, 0);
    env->cast.x_aim = WIDTH / 2;
}

int 	main(int argc, char **argv) {

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (-1);
	}

	t_env env;

	starting_parameters(&env);
	read_map(&env);
	create_the_environment(&env);
	return 0;
}
