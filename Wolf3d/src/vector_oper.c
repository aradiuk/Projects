#include "../includes/wolf3d.h"

t_i_vec create_i_vec(int x, int y)
{
    t_i_vec vec;

    vec.x = x;
    vec.y = y;

    return (vec);
}

t_vec create_vec(double x, double y)
{
    t_vec vec;

    vec.x = x;
    vec.y = y;
    return (vec);
}
