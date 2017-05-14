/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 12:34:26 by aradiuk           #+#    #+#             */
/*   Updated: 2016/12/01 12:34:36 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_strclr(char *s)
{
	int length;

	if (s != 0)
	{
		length = ft_strlen(s);
		while (length > 0)
		{
			s[length - 1] = '\0';
			length--;
		}
	}
}
