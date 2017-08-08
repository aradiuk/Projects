/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_translations_y.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 16:14:05 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/03 16:14:07 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	y_object_translation1(int keycode, t_main *main)
{
	t_sphere	*data;
	t_cone		*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "sphere") == 0)
	{
		data = (t_sphere *)main->obj[main->mode.obj_index].data;
		data->pos = keycode == 13 ?
				vec3_add(data->pos, vec3_create(0, 1, 0)) :
				vec3_sub(data->pos, vec3_create(0, 1, 0));
		data->p1 = keycode == 13 ?
				vec3_add(data->p1, vec3_create(0, 1, 0)) :
				vec3_sub(data->p1, vec3_create(0, 1, 0));
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "cone") == 0)
	{
		data1 = (t_cone *)main->obj[main->mode.obj_index].data;
		data1->p1 = keycode == 13 ?
				vec3_add(data1->p1, vec3_create(0, 1, 0)) :
				vec3_sub(data1->p1, vec3_create(0, 1, 0));
		data1->p2 = keycode == 13 ?
				vec3_add(data1->p2, vec3_create(0, 1, 0)) :
				vec3_sub(data1->p2, vec3_create(0, 1, 0));
	}
}

void	y_object_translation2(int keycode, t_main *main)
{
	t_cyl	*data;
	t_parab	*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "cylinder") == 0)
	{
		data = (t_cyl *)main->obj[main->mode.obj_index].data;
		data->p1 = keycode == 13 ?
				vec3_add(data->p1, vec3_create(0, 1, 0)) :
				vec3_sub(data->p1, vec3_create(0, 1, 0));
		data->p2 = keycode == 13 ?
				vec3_add(data->p2, vec3_create(0, 1, 0)) :
				vec3_sub(data->p2, vec3_create(0, 1, 0));
	}
	else if (ft_strcmp(main->obj[main->mode.obj_index].type, "paraboloid") == 0)
	{
		data1 = (t_parab *)main->obj[main->mode.obj_index].data;
		data1->pos = keycode == 13 ?
				vec3_add(data1->pos, vec3_create(0, 1, 0)) :
				vec3_sub(data1->pos, vec3_create(0, 1, 0));
	}
}

void	y_object_translation3(int keycode, t_main *main)
{
	t_plane *data;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "plane") == 0)
	{
		data = (t_plane *)main->obj[main->mode.obj_index].data;
		data->pos = keycode == 13 ?
					vec3_add(data->pos, vec3_create(0, 1, 0)) :
					vec3_sub(data->pos, vec3_create(0, 1, 0));
		if (data->cut != 0)
		{
			data->p2 = keycode == 13 ?
					vec3_add(data->p2, vec3_create(0, 1, 0)) :
					vec3_sub(data->p2, vec3_create(0, 1, 0));
			data->p3 = keycode == 13 ?
					vec3_add(data->p3, vec3_create(0, 1, 0)) :
					vec3_sub(data->p3, vec3_create(0, 1, 0));
			data->p4 = keycode == 13 ?
					vec3_add(data->p4, vec3_create(0, 1, 0)) :
					vec3_sub(data->p4, vec3_create(0, 1, 0));
		}
	}
}

void	y_object_translation4(int keycode, t_main *main)
{
	t_torus	*data;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "torus") == 0)
	{
		data = (t_torus *)main->obj[main->mode.obj_index].data;
		data->pos = keycode == 13 ?
					vec3_add(data->pos, vec3_create(0, 1, 0)) :
					vec3_sub(data->pos, vec3_create(0, 1, 0));
	}
}

void	y_object_rotation5(int keycode, t_main *main)
{
	t_torus	*data1;

	if (ft_strcmp(main->obj[main->mode.obj_index].type, "torus") == 0)
	{
		data1 = (t_torus *)main->obj[main->mode.obj_index].data;
		data1->axis = keycode == 13 ? m_apply(y_rot(OBJ_ROT * RAD),
			data1->axis) : m_apply(y_rot(-OBJ_ROT * RAD), data1->axis);
		y_dirextions_rot(keycode, main);
	}
}
