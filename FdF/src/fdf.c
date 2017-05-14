/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 19:09:11 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/11 18:22:54 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	text_to_array(t_fdf *fdf, char *file)
{
	int i;
	int j;

	i = 0;
	fdf->map->coord = (t_coord **)malloc(sizeof(t_coord *) * fdf->map->lines);
	while (i < fdf->map->lines)
	{
		j = 0;
		fdf->map->coord[i] = malloc(sizeof(t_coord) * fdf->map->symbols);
		while (j < fdf->map->symbols)
		{
			fdf->map->coord[i][j].x = j;
			fdf->map->coord[i][j].y = i;
			fdf->map->coord[i][j].z = ft_atoi(file);
			fdf->map->coord[i][j].color = ft_atoi_hex(file);
			while (*file != ' ' && *file != '\n' && *file != '\0')
				file++;
			while ((*file == ' ' || *file == '\n') && *file != '\0')
				file++;
			j++;
		}
		i++;
	}
}

void	read_file(int fd, t_fdf *fdf)
{
	char	*gnl_temp;
	char	*file;
	char	*temp;

	file = ft_strnew(0);
	fdf->map = (t_map *)malloc(sizeof(t_map));
	fdf->map->lines = 0;
	fdf->map->symbols = 0;
	while (get_next_line(fd, &gnl_temp))
	{
		line_validation(fdf, gnl_temp);
		temp = ft_strjoin(file, gnl_temp);
		free(file);
		free(gnl_temp);
		file = ft_strjoin(temp, "\n");
		free(temp);
		fdf->map->lines++;
	}
	if (fdf->map->lines == 0)
	{
		ft_putstr("Invalid file.\n");
		exit(0);
	}
	file[ft_strlen(file) - 1] = '\0';
	text_to_array(fdf, file);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_fdf		*fdf;

	if (argc != 2)
	{
		ft_putstr("usage: ./fdf name_of_file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	fdf->img = (t_img *)malloc(sizeof(t_img));
	read_file(fd, fdf);
	close(fd);
	matrices(fdf);
	fdf->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	fdf->mlx->mlx = mlx_init();
	fdf->mlx->window = mlx_new_window(fdf->mlx->mlx, WIDTH, HEIGHT,
									"Isometric");
	isometric(fdf);
	mlx_loop(fdf->mlx->mlx);
}
