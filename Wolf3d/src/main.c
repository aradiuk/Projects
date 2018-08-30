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


void    create_the_environment(t_env *env)
{
    env->mlx = mlx_init();
    env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3d");
    mlx_expose_hook(env->win, expose, env);
    mlx_hook(env->win, 17, 1L << 17, cross_exit, env);
    mlx_hook(env->win, 6, 1L << 6, mouse_rotation, env);
    mlx_hook(env->win, 2, 1L << 2, keyhooks, env);
    mlx_loop(env->mlx);
}

int main(int argc, char **argv) {

    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return (-1);
    }

    t_env env;

    starting_parameters(&env);
    read_map(&env);
//    create_the_environment(&env);

    return 0;
}
