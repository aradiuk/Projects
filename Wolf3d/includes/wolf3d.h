#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define WIDTH 1200
# define HEIGHT 760
# define FOV 90 * (180 / M_PI)
# define MOV_SP 0.2
# define ROT_SP 4 * M_PI / 180.
# define TEXTURES 8
# define SKY 6
# define FLOOR 7

typedef struct	s_mat
{
	double	m[2][2];
}				t_mat;

typedef struct	s_img
{
	void	*img;
	char	*ipp;
	int		bpp;
	int		endn;
	int		sline;
}				t_img;

typedef struct	s_map
{
	int x_dim;
	int y_dim;
	char **map;
}				t_map;

typedef struct  s_i_vec
{
    int x;
    int y;
}               t_i_vec;

typedef struct 	s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct	s_entity
{
	t_vec	pos;
	t_vec	dir;
}				t_entity;

typedef struct	s_texture
{
	void	*img;
	char	*ipp;
	int		width;
	int		height;
	int		bpp;
	int		endn;
	int		sline;
}				t_texture;

typedef struct	s_cast
{
	t_vec		plane;
	t_entity	ray;
	t_vec		side_dist;
	t_vec		delta_dist;
    t_vec       sky_wall;
    t_vec       sky_curr;
    t_i_vec     sky_tx;
	t_i_vec 	map;
	t_i_vec		step;
	t_i_vec		it;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			x_aim;
	double		p_wall_dist;
	double		wall_x;
	int			tx_num;
	int			tx_x;
	int			tx_y;
}				t_cast;

typedef struct	s_env
{
    void		*mlx;
    void		*win;
    t_img		img;
    char		*name;
    t_map		map;
    t_cast		cast;
	t_entity	player;
	t_texture	tx[7];
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
void	rotate_right(t_env *env);
void	rotate_left(t_env *env);

	/*	Environment */
void	create_image(t_env *env);
void	prepare_textures(t_env *env);
void	open_door(t_env *env);

    /*  Vectors */
t_i_vec create_i_vec(int x, int y);
t_vec   create_vec(double x, double y);


	/*	Raycasting	*/
void	init_geom(t_env *env);
void	calculate_step(t_env *env);
void	check_hit(t_env *env);
void	calculate_height(t_env *env);

	/*	Image	*/
void    fill_ipp(t_env *env, int img_coor, int tx_coor, int tx_num);
void    fill_middle(t_env *env, int tx_coor);
void	find_texture(t_env *env);
void	fill_image(t_env *env);
void	vertical_line(t_env *env);


	/*	Movement	*/
void	move_forward(t_env *env);
void	move_right(t_env *env);
void	move_backwards(t_env *env);
void	move_left(t_env *env);

	/*	Matrix	*/
t_mat	init_matrix(double angle);
t_vec	m_apply(t_vec vec, double angle);
t_vec	m_perp_apply(t_vec vec, int dir);

	/*	Textures */
void    prepare_textures(t_env *env);
void    init_sky(t_env *env);
void	fill_sky_and_floor(t_env *env);

#endif
