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

void    fill_sprite(t_env *env, t_i_vec img_c, int tx_coor, int tx_num)
{
    char	*img_ipp;
    int     img_coor;
    int     color;

    img_ipp = env->img.ipp;
    img_coor = img_c.x * env->img.bpp / 8 + img_c.y * env->img.sline;
    color = env->spr_tx[tx_num].ipp[tx_coor];
    if ((color & 0x00FFFFFF) != 0)
    {
        img_ipp[img_coor] = env->spr_tx[tx_num].ipp[tx_coor];
        img_ipp[img_coor + 1] = env->spr_tx[tx_num].ipp[tx_coor + 1];
        img_ipp[img_coor + 2] = env->spr_tx[tx_num].ipp[tx_coor + 2];
    }
}