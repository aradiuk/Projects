#include "../includes/wolf3d.h"

void    error(char *str)
{
    printf("error: %s\n", str);
    exit(-1);
}

void    starting_parameters(t_env *env)
{
    env->name = ft_strdup("maps/level_1");
	env->rayc.player.pos.x = 22;
	env->rayc.player.pos.y = 12;
	env->rayc.player.dir.x = -1;
	env->rayc.player.dir.y = 0;
	env->rayc.plane.x = 0;
	env->rayc.plane.y = 0.66;
	env->rayc.time = 0;
	env->rayc.old_time = 0;
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
