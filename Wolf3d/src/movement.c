#include "../includes/wolf3d.h"

void	move_forward(t_env *env)
{
	t_entity	*p;

	p = &env->player;
	if (hit_object(env, p->dir))
		return ;
	if (env->map.map[(int)(p->pos.x + p->dir.x * (MOV_SP + 0.05))][(int)p->pos.y] <= '0')
		p->pos.x += p->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y + p->dir.y * (MOV_SP + 0.05))] <= '0')
		p->pos.y += p->dir.y * MOV_SP;
}

void	move_backwards(t_env *env)
{
	t_entity	*p;

	p = &env->player;
	if (hit_object(env, create_vec(-p->dir.x, -p->dir.y)))
		return ;
	if (env->map.map[(int)(p->pos.x - p->dir.x * (MOV_SP + 0.05))][(int)p->pos.y] <= '0')
		p->pos.x -= p->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y - p->dir.y * (MOV_SP + 0.05))] <= '0')
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
            r->dir.x * (MOV_SP + 0.05))][(int)p->pos.y] <= '0')
		p->pos.x += r->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y +
			r->dir.y * (MOV_SP + 0.05))] <= '0')
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
            r->dir.x * (MOV_SP + 0.05))][(int)p->pos.y] <= '0')
		p->pos.x += r->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y +
            r->dir.y * (MOV_SP + 0.05))] <= '0')
		p->pos.y += r->dir.y * MOV_SP;
}

int		hit_object(t_env *env, t_vec dir)
{
	int		i;
	double		x;
	double		y;
	t_entity	*p;


	i = 0;
	p = &env->player;
	while (i < SPRITES)
	{
		x = p->pos.x + dir.x * (MOV_SP + 0.05);
		y = p->pos.y + dir.y * (MOV_SP + 0.05);
		if ((x - env->spr[i].pos.x) * (x - env->spr[i].pos.x) +
			(y - env->spr[i].pos.y) * (y - env->spr[i].pos.y) <= PROXIMITY)
			return (1);
		++i;
	}
	return (0);
}