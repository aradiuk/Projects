#include "../includes/wolf3d.h"

t_i_vec create_i_vec(int x, int y)
{
    t_i_vec vec;

    vec.x = x;
    vec.y = y;
    return (vec);
}

t_vec   create_vec(double x, double y)
{
    t_vec vec;

    vec.x = x;
    vec.y = y;
    return (vec);
}

t_sprite    define_sprite(double x, double y, int tx)
{
    t_sprite sprite;

    sprite.pos.x = x;
    sprite.pos.y = y;
    sprite.tx = tx;
    return (sprite);
}

int         compare_sprites(const void *first, const void *second)
{
    t_sprite    *sprite_1 = (t_sprite *)first;
    t_sprite    *sprite_2 = (t_sprite *)second;

    return (sprite_1->dist < sprite_2->dist);
}