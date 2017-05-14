/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 15:41:08 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/27 15:41:09 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		output_type(t_fract *fr)
{
	fr->out.itoaed[0] = ft_itoa(fr->fr_d.max_iter);
	if (fr->type == 0 || fr->type == 3 || fr->type == 4 || fr->type == 5)
	{
		fr->out.itoaed[1] = ft_itoa_double(fr->fr_d.cre);
		fr->out.itoaed[2] = ft_itoa_double(fr->fr_d.cim);
	}
	if (fr->type == 1 || fr->type == 2)
	{
		fr->out.itoaed[1] = ft_itoa_double(fr->fr_d.newre);
		fr->out.itoaed[2] = ft_itoa_double(fr->fr_d.newim);
	}
	fr->out.itoaed[5] = ft_itoa(fr->fr_d.color);
	fr->out.out[5] = ft_strjoin("Color: ", fr->out.itoaed[5]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, WIDTH - 85, HEIGHT - 20,
				0xFFFFFF, fr->out.out[5]);
	free(fr->out.itoaed[5]);
	free(fr->out.out[5]);
}

void		window_output(t_fract *fr)
{
	output_type(fr);
	fr->out.out[0] = ft_strjoin("N: ", fr->out.itoaed[0]);
	fr->out.out[1] = ft_strjoin("Re: ", fr->out.itoaed[1]);
	fr->out.out[2] = ft_strjoin("Im: ", fr->out.itoaed[2]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, 0, -4, 0xFFFFFF, fr->out.out[0]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, 0, 11, 0xFFFFFF, fr->out.out[1]);
	mlx_string_put(fr->mlx->mlx, fr->mlx->win, 0, 26, 0xFFFFFF, fr->out.out[2]);
	if (fr->out.mouse == 1)
		mlx_string_put(fr->mlx->mlx, fr->mlx->win, 1, HEIGHT - 20,
					0xFFFFFF, "M");
	if (fr->out.r == 1)
		mlx_string_put(fr->mlx->mlx, fr->mlx->win, 11, HEIGHT - 20,
					0xFFFFFF, "R");
	if (fr->out.i == 1)
		mlx_string_put(fr->mlx->mlx, fr->mlx->win, 21, HEIGHT - 20,
					0xFFFFFF, "I");
	fr->out.mouse = 0;
	fr->out.r = 0;
	fr->out.i = 0;
	free(fr->out.itoaed[0]);
	free(fr->out.itoaed[1]);
	free(fr->out.itoaed[2]);
	free(fr->out.out[0]);
	free(fr->out.out[1]);
	free(fr->out.out[2]);
}

void		pthreading(t_fract *fr)
{
	int				i;
	pthread_t		thread[NUM_THREADS];
	pthread_attr_t	attr;
	t_thread		*data;

	i = 0;
	data = 0;
	fr->mlx->image = mlx_new_image(fr->mlx->mlx, WIDTH, HEIGHT);
	fr->mlx->ipp = mlx_get_data_addr(fr->mlx->image, &fr->mlx->bpp,
									&fr->mlx->size_line, &fr->mlx->endian);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	while (i < NUM_THREADS)
	{
		data = thread_data(data, fr, i);
		pthread_create(&thread[i], &attr, fractal, (void *)data);
		i++;
	}
	pthread_attr_destroy(&attr);
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(thread[i++], NULL);
	mlx_put_image_to_window(fr->mlx->mlx, fr->mlx->win, fr->mlx->image, 0, 0);
	window_output(fr);
	mlx_destroy_image(fr->mlx->mlx, fr->mlx->image);
}

t_thread	*thread_data(t_thread *data, t_fract *fr, int i)
{
	int lines_per_thread;

	lines_per_thread = HEIGHT / NUM_THREADS + 1;
	data = (t_thread *)malloc(sizeof(t_thread));
	data->start = i * lines_per_thread;
	data->end = (i + 1) * lines_per_thread;
	if (data->end > HEIGHT)
		data->end = HEIGHT;
	data->fr = *fr;
	return (data);
}

void		common(t_fract *fr)
{
	fr->mlx->mlx = mlx_init();
	fr->mlx->win = mlx_new_window(fr->mlx->mlx, WIDTH, HEIGHT,
								fr->types[fr->type]);
	pthreading(fr);
	mlx_mouse_hook(fr->mlx->win, mouse_button, fr);
	mlx_hook(fr->mlx->win, 2, 3, key_hook, fr);
	mlx_loop(fr->mlx->mlx);
	free_func(fr);
}
