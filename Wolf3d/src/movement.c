#include "../includes/wolf3d.h"

void	move_forward(t_env *env)
{
	t_entity	*p;

	p = &env->player;
	if (hit_object(env, p->dir))
		return ;
	if (env->map.map[(int)(p->pos.x + p->dir.x * MOV_SP * 1.5)][(int)p->pos.y] <= '0')
		p->pos.x += p->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y + p->dir.y * MOV_SP * 1.5)] <= '0')
		p->pos.y += p->dir.y * MOV_SP;
}

void	move_backwards(t_env *env)
{
	t_entity	*p;

	p = &env->player;
	if (hit_object(env, create_vec(-p->dir.x, -p->dir.y)))
		return ;
	if (env->map.map[(int)(p->pos.x - p->dir.x * MOV_SP * 1.5)][(int)p->pos.y] <= '0')
		p->pos.x -= p->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y - p->dir.y * MOV_SP * 1.5)] <= '0')
		p->pos.y -= p->dir.y * MOV_SP;
}

void	move_right(t_env *env)
{
	t_entity	*p;
	t_entity	*r;

	p = &env->player;
	r->dir = m_perp_apply(p->dir, 1);
	if (hit_object(env, r->dir))
		return ;
	if (env->map.map[(int)(p->pos.x +
            r->dir.x * MOV_SP * 1.5)][(int)p->pos.y] <= '0')
		p->pos.x += r->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y +
			r->dir.y * MOV_SP * 1.5)] <= '0')
		p->pos.y += r->dir.y * MOV_SP;
}

void	move_left(t_env *env)
{
	t_entity	*p;
	t_entity	*r;

	p = &env->player;
	r->dir = m_perp_apply(p->dir, -1);
	if (hit_object(env, r->dir))
		return ;
	if (env->map.map[(int)(p->pos.x +
            r->dir.x * MOV_SP * 1.5)][(int)p->pos.y] <= '0')
		p->pos.x += r->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y +
            r->dir.y * MOV_SP * 1.5)] <= '0')
		p->pos.y += r->dir.y * MOV_SP;
}

int		hit_object(t_env *env, t_vec dir)
{
	int		i;
	t_vec	pos;

	i = 0;
	pos.x = env->player.pos.x + dir.x * MOV_SP * 1.5;
	pos.y = env->player.pos.y + dir.y * MOV_SP * 1.5;
	while (i < SPRITES)
	{
		if ((pos.x - env->spr[i].pos.x) * (pos.x - env->spr[i].pos.x) +
			(pos.y - env->spr[i].pos.y) * (pos.y - env->spr[i].pos.y) <= PROX)
		{
			if (env->spr[i].tx == TWO_P || env->spr[i].tx == TEN_P)
				remove_object(env, i);
			else if (env->player.points == -42 && env->spr[i].tx == 4)
			{
				prepare_level(env, env->level + 1);
				create_image(env);
				return (1);
			}
			else
				return (1);
		}
		++i;
	}
	return (0);
}
