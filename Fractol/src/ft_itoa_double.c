/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:30:15 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/03 11:30:16 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_length(int num)
{
	int i;

	i = 0;
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*str1_fill(int decimal)
{
	int		i;
	int		j;
	char	*zeroes;
	char	*decimal_res;

	decimal_res = 0;
	i = 5 - ft_length(decimal);
	j = 0;
	if (i != 0)
	{
		zeroes = ft_strnew(i);
		while (j < i)
			zeroes[j++] = '0';
		zeroes[j] = '\0';
		decimal_res = ft_strjoin(zeroes, ft_itoa(decimal));
		free(zeroes);
	}
	else
		decimal_res = ft_itoa(decimal);
	return (decimal_res);
}

char	*minus(char *result)
{
	char	*result_total;

	result_total = ft_strjoin("-", result);
	free(result);
	return (result_total);
}

char	*ft_itoa_double(double num)
{
	int		whole;
	int		decimal;
	char	*str;
	char	*str1;
	char	*result;

	whole = (int)num;
	decimal = (abs)((int)((num - whole) * 100000));
	str = ft_strjoin(ft_itoa(whole), ".");
	str1 = str1_fill(decimal);
	result = ft_strjoin(str, str1);
	free(str);
	free(str1);
	if (num < 0 && whole == 0)
		result = minus(result);
	return (result);
}
