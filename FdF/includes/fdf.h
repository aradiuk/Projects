/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 16:51:04 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/05 18:34:38 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "libft.h"

# define PI 3.141596265
# define WIDTH 2000
# define HEIGHT 1250
# define X_ANGLE 0 * PI / 180
# define Y_ANGLE 0 * PI / 180
# define Z_ANGLE 0 * PI / 180
# define SCALE 0.5
# define ROT_ON_PRESS 2

typedef struct		s_swap
{
	int up_down;
	int swapped;
}					t_swap;

typedef struct		s_matrix
{
	double	m[4][4];
}					t_matrix;

typedef struct		s_matrices
{
	t_matrix	*m_vp;
	t_matrix	*m_or;
	t_matrix	*m_tr;
	t_matrix	*m_vp_or_tr;
	t_matrix	*x_rot;
	t_matrix	*y_rot;
	t_matrix	*z_rot;
	t_matrix	*scale;
	t_matrix	*m_final;
	double		bounds[6];
}					t_matrices;

typedef struct		s_line
{
	int x0;
	int y0;
	int color0;
	int i0;
	int j0;
	int x1;
	int y1;
	int color1;
	int i1;
	int j1;
}					t_line;

typedef struct		s_coord
{
	int		x;
	int		y;
	double	z;
	int		color;
}					t_coord;

typedef struct		s_map
{
	int		symbols;
	int		lines;
	t_coord	**coord;
	t_coord **point;

}					t_map;

typedef struct		s_img
{
	void	*image;
	char	*ipp;
	int		bpp;
	int		size_line;
	int		endian;
}					t_img;

typedef struct		s_mlx
{
	void	*mlx;
	void	*window;
}					t_mlx;

typedef struct		s_fdf
{
	t_mlx		*mlx;
	t_map		*map;
	t_matrices	*mxs;
	t_line		*line;
	t_img		*img;
	t_swap		*swap;
}					t_fdf;

void				line_validation(t_fdf *fdf, char *line);
void				read_file(int fd, t_fdf	*fdf);
void				text_to_array(t_fdf *fdf, char *file);
t_matrix			*matrices(t_fdf	*fdf);
void				m_vp_declare(t_fdf *fdf);
void				m_or_declare(t_fdf *fdf);
t_matrix			*m_tr_declare(double x, double y, double z);
t_matrix			*mxs_mult(t_matrix *m1, t_matrix *m2);
void				view_check(t_fdf *fdf);
void				isometric(t_fdf	*fdf);
void				center_coords(t_fdf *fdf);
t_matrix			*x_rot_declare(double angle);
t_matrix			*y_rot_declare(double angle);
t_matrix			*z_rot_declare(double angle);
t_matrix			*m_scale_declare(double x, double y, double z);
void				draw_lines(t_fdf *fdf);
void				draw_start(t_fdf *fdf, int i, int j);
void				draw_octant(t_fdf *fdf);
void				hook_init(t_fdf *fdf);
void				rotate(t_fdf *fdf, int direction);
void				points_array(t_fdf *fdf);
void				points_calc(t_fdf *fdf);
void				translation(t_fdf *fdf, double direction);
void				center_picture(t_fdf *fdf, double dir);
int					ft_atoi_hex(char *str);
void				ipp_fill(t_fdf *fdf, int x, int y);

#endif
