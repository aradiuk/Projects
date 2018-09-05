#include <stdio.h>
#include "../includes/wolf3d.h"

int keyhooks(int keycode, t_env *env)
{
    if (keycode == 53 || keycode == 65307)
    {
        mlx_destroy_window(env->mlx, env->win);
        exit(0);
    }
    else if (keycode == 119) // forward
        move_forward(env);
    else if (keycode == 100) // right
        move_right(env);
    else if (keycode == 115) // backwards
        move_backwards(env);
    else if (keycode == 97) // left
        move_left(env);
    create_image(env);
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
    t_cast	*cast;

    cast = &env->cast;
    if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
    {
        if (x > cast->x_aim)
        {
            env->player.dir = m_apply(env->player.dir, atan((cast->x_aim - x)
            / 100.));
            cast->plane = m_apply(cast->plane, atan((cast->x_aim - x) / 100.));
            cast->x_aim = x;
        }
        else if (x < cast->x_aim)
        {
            env->player.dir = m_apply(env->player.dir, atan((cast->x_aim - x)
            / 100.));
            cast->plane = m_apply(cast->plane, atan((cast->x_aim - x) / 100.));
            cast->x_aim = x;
        }
    }
    create_image(env);
    return (0);
}