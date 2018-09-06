#include "../includes/wolf3d.h"

void	prepare_textures(t_env *env)
{
	t_texture *t;

	t = &env->tx[0];
	t[0].img = mlx_xpm_file_to_image(env->mlx, "textures/colorstone.xpm",
			&t[0].width, &t[0].height);
	t[0].ipp = mlx_get_data_addr(t[0].img, &t[0].bpp, &t[0].sline, &t[0].endn);
}