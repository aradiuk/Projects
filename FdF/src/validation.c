/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:38:38 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/24 16:40:51 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		check_hex(char **str)
{
	int i;

	i = 0;
	if (ft_strstr(*str, ",0x") != *str)
		return (1);
	*str += 3;
	while (**str != ' ' && **str)
	{
		if (ft_isdigit(**str) == 1 || (**str >= 'A' && **str <= 'F') ||
				(**str >= 'a' && **str <= 'f'))
		{
			(*str)++;
			i++;
		}
		else
			return (2);
	}
	if (i > 6 || i == 0)
		return (3);
	return (0);
}

int		symbols_validation(char *str)
{
	int	digit;

	digit = 0;
	while (*str != '\0')
	{
		if (ft_isprint(*str) == 0 && *str != '\0')
			return (1);
		while (*str == ' ' && *str != '\0')
			str++;
		if (ft_isdigit(*str) == 0 && *str != '-' && *str != ',' && *str)
			return (2);
		if (*str == '-' && ft_isdigit(*(str + 1)) == 0 && *str != '\0')
			return (3);
		if (*(str + 1) == ',' && ft_isdigit(*str) == 0 && *str != '\0')
			return (4);
		if (ft_isdigit(*str) == 1 && *str != '\0')
			digit = 1;
		if (*str == ',' && *str != '\0')
			if (check_hex(&str) != 0 || digit == 0)
				return (5);
		if (*str != '\0')
			str++;
	}
	return (digit == 0 ? 6 : 0);
}

void	line_validation(t_fdf *fdf, char *line)
{
	int i;
	int symbols;

	i = 0;
	symbols = 0;
	line = ft_strjoin(line, "\0");
	if (*line == '\0' || symbols_validation(line) != 0)
	{
		ft_putstr("Invalid file.\n");
		exit(0);
	}
	while (line[i++] != '\0' && fdf->map->lines == 0)
		if (line[i - 1] != ' ' && (line[i] == ' ' || line[i] == '\0'))
			fdf->map->symbols++;
	i = 0;
	while (line[i++] != '\0' && fdf->map->lines != 0)
		if (line[i - 1] != ' ' && (line[i] == ' ' || line[i] == '\0'))
			symbols++;
	if ((symbols != fdf->map->symbols && fdf->map->lines != 0))
	{
		ft_putstr("Invalid file.\n");
		exit(0);
	}
}
