/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 13:26:10 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/05 13:26:16 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error(int type)
{
	if (type == 1)
		ft_putstr("\t\tusage: ./RTv1 [argument]\n");
	ft_putstr("\t\tPossible arguments: [plane], [sphere], "
						"[cylinder],[cone], [composed]\n");
	if (type == 1)
		exit(0);
}

void	obj_alloc(t_rtv *rtv)
{
	rtv->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	rtv->types = (char **)malloc(sizeof(char *) * 6);
	rtv->cam = (t_camera *)malloc(sizeof(t_camera));
	rtv->types[0] = ft_strdup("plane");
	rtv->types[1] = ft_strdup("sphere");
	rtv->types[2] = ft_strdup("cylinder");
	rtv->types[3] = ft_strdup("cone");
	rtv->types[4] = ft_strdup("composed");
	rtv->types[5] = 0;
}

int		obj_type(char *str)
{
	if (ft_strcmp(str, "plane") == 0)
		return (0);
	else if (ft_strcmp(str, "sphere") == 0)
		return (1);
	else if (ft_strcmp(str, "cylinder") == 0)
		return (2);
	else if (ft_strcmp(str, "cone") == 0)
		return (3);
	else if (ft_strcmp(str, "composed") == 0)
		return (4);
	else
		return (-1);
}

void	obj_func(t_rtv *rtv)
{
	if (rtv->type == 0)
		plane_entry(rtv, 0);
	else if (rtv->type == 1)
		sphere_entry(rtv, 0);
	else if (rtv->type == 2)
		cylinder_entry(rtv, 0);
	else if (rtv->type == 3)
		cone_entry(rtv, 0);
	else if (rtv->type == 4)
		composed_entry(rtv);
}

int		main(int argc, char **argv)
{
	t_rtv	*rtv;

	if (argc != 2)
		error(1);
	rtv = (t_rtv *)malloc(sizeof(t_rtv));
	if ((rtv->type = obj_type(argv[1])) != -1)
	{
		obj_alloc(rtv);
		common(rtv);
	}
	else
		error(0);
	return (0);
}
