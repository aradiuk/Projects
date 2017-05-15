/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:08:38 by aradiuk           #+#    #+#             */
/*   Updated: 2017/05/12 17:19:14 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hook(int keycode, t_fract *fr)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 82)
		key_react(fr, 0);
	if (keycode == 69)
		key_react(fr, 1);
	if (keycode == 78)
		key_react(fr, -1);
	if (keycode == 123)
		key_react(fr, -2);
	if (keycode == 124)
		key_react(fr, 2);
	if (keycode == 125)
		key_react(fr, -3);
	if (keycode == 126)
		key_react(fr, 3);
	if (keycode == 34)
		key_react(fr, -4);
	if (keycode == 15)
		key_react(fr, 4);
	if (keycode == 49)
		key_react(fr, 5);
	if (keycode == 37)
		key_react(fr, 6);
	return (0);
}

int		mouse_hook_vary(int x, int y, void *fr)
{
	t_fract *fr_p;

	fr_p = ((t_fract *)fr);
	if (fr_p->type == 0)
	{
		if (fr_p->hooked[0] % 2 == 1 && (fr_p->fr_d.cre = JULIA_RE))
		{
			fr_p->fr_d.cim = JULIA_IM;
			fr_p->fr_d.cre += (double)(x - WIDTH / 2) / (double)WIDTH;
			fr_p->fr_d.cim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
			fr_p->out.mouse = 1;
		}
		if (fr_p->hooked[1] % 2 == 1 && (fr_p->out.r = 1) &&
													(fr_p->fr_d.cre = JULIA_RE))
			fr_p->fr_d.cre += (double)(x - WIDTH / 2) / (double)WIDTH;
		if (fr_p->hooked[2] % 2 == 1 && (fr_p->out.i = 1) &&
													(fr_p->fr_d.cim = JULIA_IM))
			fr_p->fr_d.cim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
	}
	fr_p->type == 1 ? mandel_vary(x, y, fr) : 0;
	fr_p->type == 2 ? ship_vary(x, y, fr) : 0;
	fr_p->type == 3 ? brain_vary(x, y, fr) : julia_3_4_vary(x, y, fr);
	pthreading(fr);
	xyz_output(fr, x, y);
	return (0);
}

int		mouse_button(int button, int x, int y, void *fr)
{
	if (button == 1 && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		mlx_hook(((t_fract *)fr)->mlx->win, 6, (1L << 6),
				mouse_hook_vary, fr);
		((t_fract *)fr)->hooked[0]++;
		((t_fract *)fr)->hooked[1] = 0;
		((t_fract *)fr)->hooked[2] = 0;
	}
	else if (button == 4 || button == 5)
	{
		button == 4 ? ((t_fract *)fr)->fr_d.zoom *= ZOOM_IN : 0;
		button == 5 ? ((t_fract *)fr)->fr_d.zoom *= ZOOM_OUT : 0;
		if (((t_fract *)fr)->fr_d.zoom < 0.01)
			((t_fract *)fr)->fr_d.zoom = 0.01;
		((t_fract *)fr)->fr_d.move_x += ((double)x - WIDTH / 2) /
									(WIDTH * ((t_fract *)fr)->fr_d.zoom * 3);
		((t_fract *)fr)->fr_d.move_y += ((double)y - HEIGHT / 2) /
									(HEIGHT * ((t_fract *)fr)->fr_d.zoom * 3);
	}
	pthreading(fr);
	return (0);
}

void	key_react(t_fract *fr, int code)
{
	if (code == 1 || code == -1)
	{
		if (code == 1 && fr->fr_d.max_iter > INT32_MAX - 25)
			fr->fr_d.max_iter = INT32_MAX;
		else
			fr->fr_d.max_iter += 25 * code;
		fr->fr_d.max_iter = fr->fr_d.max_iter <= 0 ? 1 : fr->fr_d.max_iter;
	}
	if (code == 2 || code == -2)
		fr->fr_d.move_x -= code / 64.;
	if (code == 3 || code == -3)
		fr->fr_d.move_y += (code / 3) / 32.;
	code == 0 ? fractal_type(fr->types[fr->type], fr) : 0;
	if (code == 4 && (++fr->hooked[1]))
		mlx_hook(fr->mlx->win, 6, (1L << 6), mouse_hook_vary, fr);
	if (code == -4 && (++fr->hooked[2]))
		mlx_hook(fr->mlx->win, 6, (1L << 6), mouse_hook_vary, fr);
	if (code == 5)
		fr->fr_d.color += fr->fr_d.color < 4 ? 1 : -fr->fr_d.color;
	if (code == 6)
		fr->fr_d.lsd_on = fr->fr_d.lsd_on == 1 ? 0 : 1;
	pthreading(fr);
}

void	mandel_vary(int x, int y, t_fract *fr)
{
	if (fr->type == 1)
	{
		if (fr->hooked[0] % 2 == 1)
		{
			fr->fr_d.newre = 0;
			fr->fr_d.newim = 0;
			fr->fr_d.newre += (double)(x - WIDTH / 2) / (double)WIDTH;
			fr->fr_d.newim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
			fr->out.mouse = 1;
		}
		if (fr->hooked[1] % 2 == 1 && (fr->out.r = 1))
		{
			fr->fr_d.newre = 0;
			fr->fr_d.newim = 0;
			fr->fr_d.newre += (double)(x - WIDTH / 2) / (double)WIDTH;
		}
		if (fr->hooked[2] % 2 == 1 && (fr->out.i = 1))
		{
			fr->fr_d.newre = 0;
			fr->fr_d.newim = 0;
			fr->fr_d.newim += (double)(y - HEIGHT / 2) / (double)HEIGHT;
		}
	}
}
