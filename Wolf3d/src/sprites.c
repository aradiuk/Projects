#include "../includes/wolf3d.h"

void	sort_sprites(t_env *env)
{
	t_entity *p;
	int	i;

	i = 0;
	p = &env->player;
	while (i < SPRITES)
	{
		env->spr[i].index = i;
		env->spr[i].dist =	(p->pos.x - env->spr[i].pos.x) *
							(p->pos.x - env->spr[i].pos.x) +
							(p->pos.y - env->spr[i].pos.y) *
							(p->pos.y - env->spr[i].pos.y);
		++i;
	}
	qsort((void *)env->spr, SPRITES, sizeof(t_sprite), compare_sprites);
}

void	iterate_sprites(t_env *env)
{
	int 		i;
	t_sprite	*s;
	t_entity	*p;
	t_cast		*c;
	t_i_vec	spr_scr;

	i = 0;
	p = &env->player;
	c = &env->cast;
	while (i < SPRITES)
	{
		s = &env->spr[i];
		c->spr.x = s->pos.x - p->pos.x;
		c->spr.y = s->pos.y - p->pos.y;
		c->inv = 1.0 / (c->plane.x * p->dir.y - p->dir.x * c->plane.y);
		c->transf.x = c->inv * (p->dir.y * c->spr.x - p->dir.x * c->spr.y);
		c->transf.y = c->inv * (-c->plane.y * c->spr.x + c->plane.x * c->spr.y);
		spr_scr.x = (int)((WIDTH / 2.) * (1 + c->transf.x / c->transf.y));
		calculate_sprites(env, s, spr_scr);
		draw_sprites(env, s, spr_scr);
		++i;
	}
}

void	calculate_sprites(t_env *env, t_sprite *s, t_i_vec spr_scr)
{
	t_entity	*p;
	t_cast		*c;

	p = &env->player;
	c = &env->cast;
	s->height = abs((int)(HEIGHT / c->transf.y));
	s->draw_start.y = (-s->height + HEIGHT) / 2.;
	s->draw_end.y = (s->height + HEIGHT) / 2.;
	if (s->draw_start.y < 0)
		s->draw_start.y = 0;
	if (s->draw_end.y >= HEIGHT)
		s->draw_end.y = HEIGHT - 1;
	s->width = abs((int)(HEIGHT / c->transf.y));
	s->draw_start.x = -s->width / 2. + spr_scr.x;
	s->draw_end.x = s->width / 2. + spr_scr.x;
	if (s->draw_start.x < 0)
		s->draw_start.x = 0;
	if (s->draw_end.x >= WIDTH)
		s->draw_end.x = WIDTH - 1;
}

void		draw_sprites(t_env *env, t_sprite *s, t_i_vec spr_scr)
{
	int		j;
	int		y;
	t_i_vec		tex;
	t_cast		*c;

	j = s->draw_start.x;
	c = &env->cast;
	while (j < s->draw_end.x)
	{
		y = s->draw_start.y;
		tex.x = (int)(256 * (j + s->width / 2. - spr_scr.x) *
				env->spr_tx[s->tx].width / (s->width * 256.));
		if (c->transf.y > 0 && j > 0 && j < WIDTH &&
			c->transf.y < env->z_buf[j])
			while (y < s->draw_end.y)
			{
				tex.y = (((y * 256 - HEIGHT * 128 + s->height * 128) *
						env->spr_tx[s->tx].height) / (s->height * 256.));
				fill_sprite(env, create_i_vec(j, y), env->spr_tx[s->tx].sline * tex.y +
													tex.x * env->spr_tx[s->tx].bpp / 8, s->tx);
				++y;
			}
		++j;
	}
}

void	sprites(t_env *env)
{
	sort_sprites(env);
	iterate_sprites(env);
}