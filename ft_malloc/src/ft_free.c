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

	page = 0;
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
	if (check_page_for_emptiness(page))
	{
		delete_page(page);
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

void	delete_page(t_page *page)
{
	t_page	*prev;
	t_page	*curr;

	curr = g_pages;
	prev = 0;
	while (curr)
	{
		if (page == curr)
		{
			if (!prev)
				g_pages = curr->next;
			else
				prev->next = curr->next;
			munmap(page, page->size);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
