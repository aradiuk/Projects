#include "../includes/wolf3d.h"

void	move_forward(t_env *env)
{
	t_entity	*p;

	p = &env->player;
	if (env->map.map[(int)(p->pos.x + p->dir.x * MOV_SP)][(int)p->pos.y] == '0')
		p->pos.x += p->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y + p->dir.y * MOV_SP)] == '0')
		p->pos.y += p->dir.y * MOV_SP;
}

void	move_backwards(t_env *env)
{
	t_entity	*p;

	p = &env->player;
	if (env->map.map[(int)(p->pos.x - p->dir.x * MOV_SP)][(int)p->pos.y] == '0')
		p->pos.x -= p->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y - p->dir.y * MOV_SP)] == '0')
		p->pos.y -= p->dir.y * MOV_SP;
}

void	move_right(t_env *env)
{
	t_entity	*p;
	t_entity	*r;

	p = &env->player;
	r->dir = m_perp_apply(p->dir, 1);
	if (env->map.map[(int)(p->pos.x + r->dir.x * MOV_SP)][(int)p->pos.y] == '0')
		p->pos.x += r->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y + r->dir.y * MOV_SP)] == '0')
		p->pos.y += r->dir.y * MOV_SP;

}

void	move_left(t_env *env)
{
	t_entity	*p;
	t_entity	*r;

	p = &env->player;
	r->dir = m_perp_apply(p->dir, -1);
	if (env->map.map[(int)(p->pos.x + r->dir.x * MOV_SP)][(int)p->pos.y] == '0')
		p->pos.x += r->dir.x * MOV_SP;
	if (env->map.map[(int)p->pos.x][(int)(p->pos.y + r->dir.y * MOV_SP)] == '0')
		p->pos.y += r->dir.y * MOV_SP;
}
