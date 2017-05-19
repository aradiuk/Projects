/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 19:15:25 by aradiuk           #+#    #+#             */
/*   Updated: 2017/05/10 19:15:26 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>

# define WIDTH 1200
# define HEIGHT 720
# define ASPECT (double)WIDTH / (double)HEIGHT
# define FOV 30. * M_PI / 180.
# define LIGHT_SOURCES 1
# define AMBIENT_R 0.25
# define AMBIENT_G 0.25
# define AMBIENT_B 0.25
# define DIFF_R 0.5
# define DIFF_G 0.5
# define DIFF_B 0.5
# define SP_R 0.2
# define SP_G 0.2
# define SP_B 0.2
# define GL 100
# define SHADOW 0.2
# define ROT_ANGLE 15 * M_PI / 180

typedef struct		s_vec3
{
	double x;
	double y;
	double z;
}					t_vec3;

typedef struct		s_ray
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	n[3];
	t_vec3	l[3];
	t_vec3	h[3];
	t_vec3	v;
	double	t;
}					t_ray;

typedef	struct		s_color
{
	t_vec3	rgb;
	double	r;
	double	g;
	double	b;
	int		final_color;
}					t_color;

typedef	struct		s_camera
{
	t_vec3	pos;
	t_vec3	start;
	t_ray	ray;
}					t_camera;

typedef	struct		s_light
{
	t_vec3	pos;
	t_color	color;
	t_ray	sh_ray;
	double	sh_t[4];
	int		block;
}					t_light;

typedef struct		s_plane
{
	t_vec3	normal;
	t_vec3	pos;
	t_color	color;
}					t_plane;

typedef	struct		s_sphere
{
	t_vec3		pos;
	t_color		color;
	double		rad;
}					t_sphere;

typedef	struct		s_cylinder
{
	t_vec3	pos;
	t_vec3	rot;
	t_vec3	axis;
	t_vec3	a;
	t_vec3	c;
	t_color	color;
	double	rad;
}					t_cylinder;

typedef struct		s_cone
{
	t_vec3	pos;
	t_vec3	rot;
	t_vec3	axis;
	t_vec3	a_c;
	t_vec3	c_c;
	t_color	color;
	double	a_s;
	double	c_s;
	double	a;
	double	b;
	double	angle;
}					t_cone;

typedef struct		s_composed
{
	double	*plane_t;
	double	*sphere_t;
	double	*cyl_t;
	double	*cone_t;
	double	t[4];
	int		type;
	int		plane_num;
	int		sphere_num;
	int		cyl_num;
	int		cone_num;
}					t_composed;

typedef struct		s_mlx
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*ipp;
	int		bpp;
	int		size_line;
	int		endian;
}					t_mlx;

typedef struct		s_matrix
{
	double m[4][4];
}					t_matrix;

typedef struct		s_matrices
{
	t_matrix	rot_x_cam;
	t_matrix	rot_y_cam;
	t_matrix	rot_z_cam;
	t_matrix	rot_cam;
	t_matrix	rot_x_dir;
	t_matrix	rot_y_dir;
	t_matrix	rot_z_dir;
	t_matrix	rot_dir;
	t_vec3		cam_angle;
	t_vec3		dir_angle;
}					t_matrices;

typedef struct		s_rtv
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_cone		*cone;
	t_composed	*comp;
	t_mlx		*mlx;
	t_camera	*cam;
	t_light		light[3];
	t_matrices	mxs;
	char		**types;
	int			num[4];
	int			type;
}					t_rtv;

int					obj_type(char *str);
int					color_count(t_rtv *rtv, t_color color);
double				find_max(double *t_object, int size);
void				obj_alloc(t_rtv	*rtv);
void				start_alloc(t_rtv *rtv);
void				error(int type);
void				common(t_rtv *rtv);
void				cam_params(t_rtv *rtv);
void				ipp_fill(t_rtv *rtv, int x, int y, int color);
void				camera_rotation(t_rtv *rtv, int dir);
void				new_image(t_rtv *rtv);
void				free_func(t_rtv *rtv);
void				null_rgb(t_color *color);
void				cam_check(t_rtv *rtv);

/*
**	Object parameters functions
*/

void				plane_params(t_rtv *rtv);
void				sphere_params(t_rtv *rtv);
void				cylinder_params(t_rtv *rtv);
void				cone_params(t_rtv *rtv);
void				composed_params(t_rtv *rtv);

/*
** Plane functions
*/

double				p_intersection_find(t_rtv *rtv, t_plane	*plane, t_ray *ray);
void				plane_vectors(t_rtv *rtv, t_plane *plane, t_ray *ray);

/*
** Sphere functions
*/

double				s_intersection_find(t_rtv *rtv, t_sphere *sphere,
																	t_ray *ray);
double				s_t_count(t_ray *ray, double disc, double b, double a);
void				sphere_vectors(t_rtv *rtv, t_sphere *sphere, t_ray *ray);

/*
** Cylinder functions
*/

int					cl_color_count(t_rtv *rtv);
double				cl_intersection_find(t_rtv *rtv, t_cylinder *cyl,
																	t_ray *ray);
double				cl_t_count(t_ray *ray, double disc, double b, double a);
void				cylinder_vectors(t_rtv *rtv, t_cylinder *cyl, t_ray *ray);
t_vec3				cl_disk_center(t_cylinder *cyl, t_ray *ray);

/*
** Cone funtions
*/

double				cn_intersection_find(t_rtv *rtv, t_cone *cone, t_ray *ray);
double				cn_disk_count(t_cone *cone);
double				cn_t_count(t_ray *ray, double disc, double b, double a);
void				cone_vectors(t_rtv *rtv, t_cone *cone, t_ray *ray);

/*
** Composed funtions
*/

double				cp_intersection_find(t_rtv *rtv, t_ray *ray);
double				cp_t_count(t_rtv *rtv);
double				shadowed(t_rtv *rtv, int i);
double				planes_intersection(t_rtv *rtv, t_ray *ray);
double				spheres_intersection(t_rtv *rtv, t_ray *ray);
double				cylinders_intersection(t_rtv *rtv, t_ray *ray);
double				cones_intersection(t_rtv *rtv, t_ray *ray);
void				composed_entry(t_rtv *rtv);
void				shadow_count(t_rtv *rtv, double *r, double *g, double *b);
t_color				*obj_color(t_rtv *rtv, t_ray *ray);

/*
**	Functions for vector operations
*/

double				vec3_length(t_vec3 vec);
double				vec3_dp(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_create(double x, double y, double z);
t_vec3				vec3_norm(t_vec3 vector);
t_vec3				vec3_invert(t_vec3	vector);
t_vec3				vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_sub(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_mult(t_vec3 vec, double multiplier);

/*
** 	Matrix functions
*/

void				matrices(t_rtv *rtv);
t_matrix			m_tr(t_vec3 vec);
t_matrix			m_rot(t_vec3 u, t_vec3 v, t_vec3 w);
t_matrix			m_mult(t_matrix m1, t_matrix m2);
t_matrix			x_rot(double angle);
t_matrix			y_rot(double angle);
t_matrix			z_rot(double angle);
t_vec3				m_apply(t_matrix matrix, t_vec3 vec);

#endif
