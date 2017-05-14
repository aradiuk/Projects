/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:15:50 by aradiuk           #+#    #+#             */
/*   Updated: 2017/03/20 11:15:56 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		base_length(char *base)
{
	int i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

int		ret_res(char *str, char *base, char *base1, int i)
{
	int j;
	int check;
	int res;

	res = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
	{
		j = 0;
		check = 0;
		while (base[j] != '\0')
		{
			if (base[j] == str[i] || base1[j] == str[i])
			{
				check = 1;
				break ;
			}
			j++;
		}
		if (check == 0)
			return (0);
		res = res * base_length(base) + j;
		i++;
	}
	return (res);
}

int		ft_atoi_hex(char *str)
{
	int		i;
	int		result;
	char	*base;
	char	*base1;

	base = "0123456789abcdef";
	base1 = "0123456789ABCDEF";
	i = 0;
	while (ft_isdigit(str[i]) == 0)
		i++;
	while (str[i] != 'x' && str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == 'x')
		result = ret_res(str, base, base1, i + 1);
	else
		result = 0xFFFFFF;
	return (result);
}
