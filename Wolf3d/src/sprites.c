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

void	calculate_sprites(t_env *env)
{
	int 		i;
	t_sprite	*s;
	t_entity	*p;
	t_cast		*c;

	i = 0;
	s = &env->spr[0];
	p = &env->player;
	c = &env->cast;
	while (i < SPRITES)
	{
		c->spr.x = s[s[i].index].pos.x - p->pos.x;
		c->spr.y = s[s[i].index].pos.y - p->pos.y;
		c->inv = 1.0 / (c->plane.x * p->dir.y - p->dir.x * c->plane.y);
		c->transf.x = c->inv * (p->dir.y * c->spr.x - p->dir.x * c->spr.y);
		c->transf.y = c->inv * (-c->plane.y * c->spr.x + c->plane.x * c->spr.y);
		
		++i;
	}
}

void	sprites(t_env *env)
{
	define_sprites(env);
	sort_sprites(env);
	calculate_sprites(env);

}