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

void	sprites(t_env *env)
{
	int i;

	i = 0;
	define_sprites(env);
	sort_sprites(env);
	while (i < SPRITES)
	{
		
		++i;
	}
}