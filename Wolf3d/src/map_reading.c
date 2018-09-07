#include "../includes/wolf3d.h"
#include <fcntl.h>

void	get_map_dimensions(int fd, t_env *env)
{
	char	*line;
	char	*free_line;
	get_next_line(fd, &line);
	int i;

	i = -1;
	free_line = line;
	while (line[++i] != '\0')
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			error("not numerical map dimensions");
	while(*line && !ft_isdigit(*line))
		++line;
	env->map.x_dim = ft_atoi(line);
	while (*line && ft_isdigit(*line))
		++line;
	env->map.y_dim = ft_atoi(line);
	if (env->map.x_dim < 3 || env->map.x_dim > 199)
		error("x dimension is out of range");
	if (env->map.y_dim < 3 || env->map.y_dim > 199)
		error("y dimension is out of range");
	free(free_line);
}

void	validate_line(char *line, t_env *env, int line_num)
{
	int i;

	i = 0;
	if ((int)ft_strlen(line) != env->map.x_dim)
		error("one of the map lines is out of range");
	if (!ft_isdigit(line[0]) || line[0] == '0' ||
		!ft_isdigit(line[env->map.x_dim - 1]) || line[env->map.x_dim - 1] == '0')
		error("your side walls are broken");
	if (line_num == 0 || line_num == env->map.y_dim - 1)
	{
		while (++i < env->map.x_dim - 1)
			if (!ft_isdigit(line[i]) || line[i] == '0')
				error("top or bottom wall is broken");
	}
	else
	{
		while (++i < env->map.x_dim - 1)
			if (!ft_isdigit(line[i]))
				error("map contains an illegal character");
	}
}

void	get_map(int fd, t_env *env)
{
	int		i;
	char 	*line;

	i = 0;
	env->map.map = (char **)malloc(sizeof(char *) * env->map.y_dim + 1);
	if (!env->map.map)
		error("malloc unsuccessful");
	env->map.map[env->map.y_dim] = 0;
	while (i < env->map.y_dim && get_next_line(fd, &line) > 0)
	{
		validate_line(line, env, i);
		env->map.map[i] = ft_strdup(line);
		free(line);
		++i;
	}
	if (i != env->map.y_dim)
		error("one of the map columns is out of range");
	if (get_next_line(fd, &line) > 0)
	{
		free(line);
		error("map has too many lines");
	}
}

void	read_map(t_env *env)
{
	int		fd;

	fd = open(env->name, O_RDONLY);
	if (fd == -1)
		error("can't open map file");
	get_map_dimensions(fd, env);
	get_map(fd, env);
		// CHECK FOR POSITION TO BE CLEAR
	if (env->map.map[(int)env->player.pos.x][(int)env->player.pos.y] != '0')
		error("player position isn't empty");
}

