/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 13:26:49 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/05 13:26:52 by aradiuk          ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 600
# define ASPECT (double)WIDTH / (double)HEIGHT
# define FOV 30. * (double)M_PI / 180.
# define AMBIENT_R 0.2
# define AMBIENT_G 0.2
# define AMBIENT_B 0.2
# define DIFF_R 0.25
# define DIFF_G 0.25
# define DIFF_B 0.25
# define SPEC_R 0.25
# define SPEC_G 0.25
# define SPEC_B 0.25
# define GLS 100
# define LIGHT_SOURCES 1

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
	t_vec3	v;
	t_vec3	n;
	t_vec3	l[3];
	t_vec3	h[3];
	double	t;
}					t_ray;

typedef	struct		s_color
{
	t_vec3	rgb;
	double	spec;
	int		final_color;
}					t_color;

typedef	struct		s_camera
{
	t_vec3	pos;
	t_vec3	gaze;
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;
	t_ray	ray;
	t_vec3	vec3_x;
	t_vec3	vec3_y;
	t_vec3	vec3_z;
	t_vec3	cam_to_g;
}					t_camera;

typedef	struct		s_light
{
	t_vec3	pos;
	t_color	color;
	double	sh_t[4];
	t_ray	sh_ray[3];
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
	double		rad;
	t_color		color;
}					t_sphere;

typedef	struct		s_cylinder
{
	t_vec3	pos;
	t_vec3	rot;
	t_vec3	axis;
	t_vec3	a;
	t_vec3	c;
	double	rad;
	t_color	color;
}					t_cylinder;

typedef struct		s_cone
{
	t_vec3	pos;
	t_vec3	rot;
	t_vec3	axis;
	t_vec3	a_c;
	t_vec3	c_c;
	double	a_s;
	double	c_s;
	double	a;
	double	b;
	double	angle;
	t_color	color;
}					t_cone;

typedef struct		s_composed
{
	double	t[4];
	int		type;
}					t_composed;

typedef struct		s_mlx
{
	void	*mlx;
	void	*window;
}					t_mlx;

typedef struct		s_matrix
{
	double m[4][4];
}					t_matrix;

typedef struct 		s_matrices
{
	t_matrix	tr;
	t_matrix	rot;
	t_matrix	multed;
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
	int			type;
	char		**types;
}					t_rtv;

int					obj_type(char *str, t_rtv *rtv);
void				obj_alloc(t_rtv	*rtv);
void				obj_func(t_rtv *rtv);
void				error(int type);
void				common(t_rtv *rtv);
int					color_count(t_rtv *rtv, t_color color);

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

void				plane_entry(t_rtv *rtv);
double				p_intersection_find(t_rtv *rtv, t_ray *ray);
void				plane_vectors(t_rtv *rtv, t_ray *ray);

/*
** Sphere functions
*/

void				sphere_entry(t_rtv *rtv);
double				s_intersection_find(t_rtv *rtv, t_ray *ray);
double				s_t_count(t_ray *ray, double disc, double b, double a);
void				sphere_vectors(t_rtv *rtv, t_ray *ray);

/*
** Cylinder functions
*/

void				cylinder_entry(t_rtv *rtv);
double				cl_intersection_find(t_rtv *rtv, t_ray *ray);
t_vec3				cl_disk_center(t_rtv *rtv, t_ray *ray);
int					cl_color_count(t_rtv *rtv);
void				cylinder_vectors(t_rtv *rtv, t_ray *ray);
double				cl_t_count(t_ray *ray, double disc, double b, double a);

/*
** Cone funtions
*/

void				cone_entry(t_rtv *rtv);
double				cn_intersection_find(t_rtv *rtv, t_ray *ray);
double				cn_disk_count(t_rtv *rtv);
double				cn_t_count(t_ray *ray, double disc, double b, double a);
void				cone_vectors(t_rtv *rtv, t_ray *ray);

/*
** Composed funtions
*/

void				composed_entry(t_rtv *rtv);
double				cp_intersection_find(t_rtv *rtv);
double				cp_t_count(t_rtv *rtv);
t_color				*obj_color(t_rtv *rtv, t_ray *ray);
double				shadowed(t_rtv *rtv, int i);
void				shadow_count(t_rtv *rtv, double *r, double *g, double *b);

/*
**	Functions for vector operations
*/

t_vec3				vec3_create(double x, double y, double z);
t_vec3				vec3_norm(t_vec3 vector);
t_vec3				vec3_invert(t_vec3	vector);
double				vec3_length(t_vec3 vec);
double				vec3_dp(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_cp(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_sub(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_mult(t_vec3 vec, double multiplier);

/*
**  REMOVE THIS AT THE END!!!
*/

void				vec3_print(char *str, t_vec3 vec);
t_matrix			m_tr(t_vec3 vec);
t_matrix			m_rot(t_vec3 u, t_vec3 v, t_vec3 w);
t_matrix			m_mult(t_matrix m1, t_matrix m2);
t_vec3				m_apply(t_matrix matrix, t_vec3 vec);
void				matrices(t_rtv *rtv);
void				m_print(t_matrix matrix);

/*
** 	REMOVE THIS AT THE END!!!
*/

#endif
