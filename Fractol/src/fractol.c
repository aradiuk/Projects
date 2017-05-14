/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 14:42:22 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/25 14:42:24 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initial_conditions(t_fract *fr)
{
	fr->fr_d.move_x = 0;
	fr->fr_d.move_y = 0;
	fr->fr_d.zoom = 1;
	fr->fr_d.max_iter = MAX_ITER;
	fr->hooked[0] = 0;
	fr->hooked[1] = 0;
	fr->hooked[2] = 0;
	fr->out.mouse = 0;
	fr->fr_d.cre = 0;
	fr->fr_d.cim = 0;
	fr->out.r = 0;
	fr->out.i = 0;
	fr->fr_d.color = 0;
	fr->fr_d.pr = 0;
	fr->fr_d.pi = 0;
	fr->fr_d.newre = 0;
	fr->fr_d.newim = 0;
	fr->fr_d.pr = 0;
	fr->fr_d.pi = 0;
	fr->fr_d.lsd_on = 0;
	colors(fr);
}

int		fractal_type(char *str, t_fract *fr)
{
	initial_conditions(fr);
	if (ft_strcmp(str, "julia") == 0 || ft_strcmp(str, "brain") == 0 ||
			ft_strcmp(str, "julia_3") == 0 || ft_strcmp(str, "julia_4") == 0)
		return (julias(str, fr));
	if (ft_strcmp(str, "mandelbrot") == 0)
	{
		fr->fr_d.move_x = -0.5;
		return (1);
	}
	if (ft_strcmp(str, "burning_ship") == 0)
	{
		fr->fr_d.move_x = -0.5;
		fr->fr_d.move_y = -0.5;
		return (2);
	}
	return (-1);
}

void	fr_alloc(t_fract *fr)
{
	fr->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	fr->types = (char **)malloc(sizeof(char *) * 7);
	fr->types[0] = ft_strdup("julia");
	fr->types[1] = ft_strdup("mandelbrot");
	fr->types[2] = ft_strdup("burning_ship");
	fr->types[3] = ft_strdup("brain");
	fr->types[4] = ft_strdup("julia_3");
	fr->types[5] = ft_strdup("julia_4");
	fr->types[6] = 0;
	fr->out.itoaed[6] = 0;
	fr->out.out[6] = 0;
}

void	error(int ex)
{
	static int i;

	if (ex == 1)
		ft_putstr("\t\t  usage: ./fract [argument1] [argument2] ... "
						"[argumentN]\n");
	if (i == 0)
		ft_putstr("\t\t  List of possible arguments: "
					"[julia], [julia_3], [julia_4],"
					"[mandelbrot], [burning_ship], [brain]\n");
	if (ex == 1)
		exit(0);
	i++;
}

int		main(int argc, char **argv)
{
	pid_t		pid;
	int			i;
	t_fract		*fr;

	i = 1;
	argc < 2 ? error(1) : 0;
	fr = (t_fract *)malloc(sizeof(t_fract));
	fr_alloc(fr);
	while (i < argc)
	{
		if ((fr->type = fractal_type(argv[i], fr)) != -1)
		{
			pid = fork();
			if (pid == 0)
			{
				common(fr);
				break ;
			}
		}
		else
			error(0);
		i++;
	}
	free_func(fr);
	return (0);
}
