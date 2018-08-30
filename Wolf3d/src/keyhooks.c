#include <stdio.h>
#include "wolf3d.h"

int keyhooks(int keycode, t_env *env)
{
    if (keycode == 53)
    {
        mlx_destroy_window(env->mlx, env->win);
        exit(0);
    }
    return (0);
}

int cross_exit(t_env *env)
{
    mlx_destroy_window(env->mlx, env->win);
    exit(0);
    return (0);
}

int     mouse_rotation(int x, int y, t_env *env)
{
    (void)env;
    x = y;
    y = x;
//    printf("I'm rotating!\n");
    return (0);
}