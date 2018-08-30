#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define FOV 90 * (180 / PI)

typedef struct	s_img
{
	void	*img;
	int		bpp;
	int		endian;
	int		sizeline;
}				t_img;

typedef struct	s_map
{
	int x_dim;
	int y_dim;
	char **map;
}				t_map;

typedef struct 	s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct	s_player
{
	t_vec	pos;
	t_vec	dir;
}				t_player;

typedef struct	s_rayc
{
	t_player	player;
	t_vec		plane;
	double		time;
	double		old_time;

}				t_rayc;

typedef struct	s_env
{
    void   		*mlx;
    void    	*win;
    t_img		img;
    char		*data;
    char		*name;
    t_map		map;
    t_rayc		rayc;
}               t_env;

	/* Main */
void	error(char *str);
void    starting_parameters(t_env *env);
void    create_the_environment(t_env *env);

	/*	Map reading */
void	read_map(t_env *env);
void	get_map_dimensions(int fd, t_env *env);
void	get_map(int fd, t_env *env);
void	validate_line(char *line, t_env *env, int line_num);

	/*	Keyhooks */
int		keyhooks(int keycode, t_env *env);
int     cross_exit(t_env *env);
int		mouse_rotation(int x, int y, t_env *env);

	/*	Environment */
int		expose(t_env *env);
void	create_image(t_env *env);
void	raycasting(t_env *env);

#endif 
