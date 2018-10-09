/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:13:26 by aradiuk           #+#    #+#             */
/*   Updated: 2018/10/09 16:13:30 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	end_game(t_env *env)
{
	int i;

	i = 0;
	while (i <= env->map.y_dim)
	{
		free(env->map.map[i]);
		++i;
	}
	free(env->map.map);
	mlx_destroy_window(env->mlx, env->win);
	system("killall afplay");
	exit(1);
}

void	error(char *str)
{
	printf("error: %s\n", str);
	system("killall afplay");
	exit(-1);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (-1);
	}
	system("afplay audio.mp3 &");
	prepare_level(&env, 1);
	create_the_environment(&env);

	return (0);
}
