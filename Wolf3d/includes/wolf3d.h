#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define WIDTH 800
# define HEIGHT 600
# define FOV 90 * (180 / M_PI)
# define MOV_SP 0.2
# define ROT_SP 4 * M_PI / 180.
# define SPRITES 5
# define SPR_TX 4
# define TEXTURES 9
# define SKY 6
# define FLOOR 7
# define DOOR 8
# define SC_DOOR 3
# define PROX 0.075
# define TWO_P 2
# define TEN_P 3

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
	int		points;
}				t_entity;

typedef struct	s_sprite
{
	t_vec		pos;
	double		dist;
	int			index;
	int			tx;
	int			height;
	int			width;
	t_i_vec		draw_start;
	t_i_vec		draw_end;
}				t_sprite;

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
	t_vec		sky_wall;
	t_vec		sky_curr;
	t_vec		spr;
	t_vec		transf;
	t_i_vec		sky_tx;
	t_i_vec 	map;
	t_i_vec		step;
	t_i_vec		it;
	double		p_wall_dist;
	double		wall_x;
	double		inv;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			x_aim;
	int			tx_num;
	int			tx_x;
	int			tx_y;
}				t_cast;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	char		*name;
	double		z_buf[WIDTH];
	int			level;
	t_img		img;
	t_map		map;
	t_cast		cast;
	t_entity	player;
	t_sprite	spr[SPRITES];
	t_texture	tx[TEXTURES];
	t_texture	spr_tx[SPR_TX];
}				t_env;

	/* Main */
void		error(char *str);
void		create_the_environment(t_env *env);
void		level_1(t_env *env);

	/*	Map reading */
void		read_map(t_env *env);
void		get_map_dimensions(int fd, t_env *env);
void		get_map(int fd, t_env *env);
void		validate_line(char *line, t_env *env, int line_num);
void		validate_position(t_env *env);

	/*	Keyhooks */
int			keyhooks(int keycode, t_env *env);
int			cross_exit(t_env *env);
int			mouse_rotation(int x, int y, t_env *env);
void		rotate_right(t_env *env);
void		rotate_left(t_env *env);

	/*	Environment */
void		create_image(t_env *env);
void		prepare_textures(t_env *env);
void		open_door(t_env *env);
void		remove_object(t_env *env, int i);

	/*	Vectors */
t_i_vec		create_i_vec(int x, int y);
t_vec		create_vec(double x, double y);
t_sprite	define_sprite(double x, double y, int tx);
int			compare_sprites(const void *first, const void *second);
void		fill_sprite(t_env *env, t_i_vec img_c, int tx_coor, int tx_num);

	/*	Raycasting	*/
void		init_geom(t_env *env);
void		calculate_step(t_env *env);
void		check_hit(t_env *env);
void		calculate_height(t_env *env);

	/*	Image	*/
void		fill_ipp(t_env *env, int img_coor, int tx_coor, int tx_num);
void		fill_middle(t_env *env, int tx_coor);
void		find_texture(t_env *env);
void		fill_image(t_env *env);
void		vertical_line(t_env *env);

	/*	Movement	*/
void		move_forward(t_env *env);
void		move_right(t_env *env);
void		move_backwards(t_env *env);
void		move_left(t_env *env);
int			hit_object(t_env *env, t_vec dir);

	/*	Matrix	*/
t_mat		init_matrix(double angle);
t_vec		m_apply(t_vec vec, double angle);
t_vec		m_perp_apply(t_vec vec, int dir);

	/*	Textures */
void		prepare_textures(t_env *env);
void		init_sky(t_env *env);
void		fill_sky_and_floor(t_env *env);
void		prepare_sprites(t_env *env);

	/*	Sprites */
void		sprites(t_env *env);
void		sort_sprites(t_env *env);
void		iterate_sprites(t_env *env);
void		calculate_sprites(t_env *env, t_sprite *s, t_i_vec spr_scr);
void		draw_sprites(t_env *env, t_sprite *s, t_i_vec spr_scr);

	/*	Levels */
void		define_sprites(t_env *env);
void		starting_parameters_1(t_env *env);
void		starting_parameters_2(t_env *env);
void		prepare_level(t_env *env, int level);
void		end_game(t_env *env);


#endif
