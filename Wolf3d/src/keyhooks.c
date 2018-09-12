#include <stdio.h>
#include "../includes/wolf3d.h"

int keyhooks(int keycode, t_env *env)
{
    if (keycode == 53 || keycode == 65307)
    {
        mlx_destroy_window(env->mlx, env->win);
        exit(0);
    }
    else if (keycode == 13 || keycode == 119 || keycode == 126) // forward
        move_forward(env);
    else if (keycode == 2 || keycode == 100) // right
        move_right(env);
    else if (keycode == 1 || keycode == 115 || keycode == 125) // backwards
        move_backwards(env);
    else if (keycode == 0 || keycode == 97) // left
        move_left(env);
    else if (keycode == 124 || keycode == 65363) // rot_right
      rotate_right(env);
    else if (keycode == 123 || keycode == 65361) // rot_right
        rotate_left(env);
    else if (keycode == 1 || keycode == 32) //  Door activator
        open_door(env);
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
            env->player.dir = m_apply(env->player.dir, -ROT_SP);
            cast->plane = m_apply(cast->plane, -ROT_SP);
            cast->x_aim = x;
        }
        else if (x < cast->x_aim)
        {
            env->player.dir = m_apply(env->player.dir, ROT_SP);
            cast->plane = m_apply(cast->plane, ROT_SP);
            cast->x_aim = x;
        }
        create_image(env);
    }
    return (0);
}

void    rotate_right(t_env *env)
{
    env->player.dir = m_apply(env->player.dir, -ROT_SP);
    env->cast.plane = m_apply(env->cast.plane, -ROT_SP);
}

void    rotate_left(t_env *env)
{
    env->player.dir = m_apply(env->player.dir, ROT_SP);
    env->cast.plane = m_apply(env->cast.plane, ROT_SP);
}