/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:07:48 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/10 11:29:06 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		get_page_size(t_page *page)
{
	if (page)
		return (page->size - sizeof(t_page));
	else
		return (0);
}

ptrdiff_t	get_page_address(t_page *page)
{
	if (page)
		return (page->address + sizeof(t_page));
	else
		return (0);
}

size_t		get_allocation_size(t_info *allocation)
{
	if (allocation)
		return (allocation->size - sizeof(t_info));
	else
		return (0);
}

ptrdiff_t	get_allocation_address(t_info *allocation)
{
	if (allocation)
		return (allocation->address + sizeof(t_info));
	else
		return (0);
}

ptrdiff_t	get_allocation_end(t_info *allocation)
{
	if (allocation)
		return (get_allocation_address(allocation) +
				get_allocation_size(allocation));
	else
		return (0);
}
