/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:22:44 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/10 11:26:05 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free(void *ptr)
{
	t_page	*page;
	t_info	*previous;
	t_info	*allocation;
	t_info	*next;

	if (!ptr)
		return ;
	allocation = find_allocation((ptrdiff_t)ptr, &previous);
	if (allocation)
	{
		page = allocation->page;
		next = allocation->next;
		page->empty += allocation->size;
		if (!previous)
			page->allocations = next;
		else
			previous->next = next;
		ft_bzero(allocation, sizeof(t_info));
	}
}

t_info	*find_allocation(ptrdiff_t address, t_info **previous)
{
	t_page	*page;
	t_info	*allocation;

	page = g_pages;
	while (page)
	{
		*previous = 0;
		allocation = page->allocations;
		while (allocation)
		{
			if ((ptrdiff_t)get_allocation_address(allocation) == address)
				return (allocation);
			*previous = allocation;
			allocation = allocation->next;
		}
		page = page->next;
	}
	previous = 0;
	return (0);
}

int		is_enough_size(t_page *page, t_info *allocation, size_t size)
{
	if ((size_t)(page->address + page->size -
		get_allocation_end(allocation)) >= size)
		return (1);
	else
		return (0);
}
