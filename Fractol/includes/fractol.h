/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 14:15:02 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/04 14:15:04 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 100
# define NUM_THREADS 81
# define ZOOM_IN 1.1
# define ZOOM_OUT 0.9
# define JULIA_RE -0.7
# define JULIA_IM 0.27015
# define BRAIN_RE -0.86597
# define BRAIN_IM 0.09237

typedef struct	s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct	s_comp
{
	double	move_x;
	double	move_y;
	t_color	color_s[5];
	t_color	color_e[5];
	int		color;
	double	lsd[3];
	int		lsd_on;
	int		max_iter;
	double	pr;
	double	pi;
	double	cre;
	double	cim;
	double	newre;
	double	newim;
	double	zoom;
}				t_comp;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*image;
	char	*ipp;
	int		bpp;
	int		size_line;
	int		endian;
}				t_mlx;

typedef	struct	s_out
{
	char	*out[7];
	char	*itoaed[7];
	int		mouse;
	int		r;
	int		i;
}				t_out;

typedef struct	s_fract
{
	int		type;
	char	**types;
	int		hooked[3];
	t_mlx	*mlx;
	t_comp	fr_d;
	t_out	out;
}				t_fract;

typedef struct	s_thread
{
	int		start;
	int		end;
	t_fract	fr;
}				t_thread;

int				key_hook(int keycode, t_fract *fr);
int				fractal_type(char *str, t_fract *fr);
void			fr_alloc(t_fract *fr);
void			error(int exit);
void			common(t_fract *fr);
t_thread		*thread_data(t_thread *data, t_fract *fr, int i);
void			pthreading(t_fract *fr);
void			*fractal(void *data);
int				algorithm(t_comp fr_d, int type);
void			key_react(t_fract *fr, int code);
int				mouse_button(int button, int x, int y, void *param);
int				mouse_hook_vary(int x, int y, void *fr);
int				gradient(t_comp fr_d, int i);
void			initial_conditions(t_fract *fr);
char			*ft_itoa_double(double num);
void			xyz_output(t_fract *fr, int x, int y);
void			mandel_vary(int x, int y, t_fract *fr);
void			ship_vary(int x, int y, t_fract *fr);
void			brain_vary(int x, int y, t_fract *fr);
void			colors(t_fract *fr);
void			colors_1(t_fract *fr);
void			julia_3_4(t_comp *fr_d, int type, double *oldre, double *oldim);
int				julias(char *str, t_fract *fr);
void			julia_3_4_vary(int x, int y, t_fract *fr);
void			free_func(t_fract *fr);

#endif
