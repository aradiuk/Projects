/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:42:03 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/09 12:02:24 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_page	*g_pages = 0;

void	*malloc(size_t size)
{
	t_page	*page;
	t_type	type;
	void	*allocation;

	if (!size)
		return (0);
	if (size <= TINY)
		type = tiny;
	else if (size <= SMALL)
		type = small;
	else
		type = large;
	if (g_pages)
		page = get_page(type, size);
	else
		page = get_new_page(type, size);
	allocation = get_new_allocation(page, size);
	return ((void *)get_allocation_address(allocation));
}

t_info	*allocate_chunk(ptrdiff_t address, size_t size, t_page *page)
{
	t_info *allocation;

	allocation = 0;
	ft_bzero((void *)address, sizeof(t_info));
	allocation = (t_info *)address;
	allocation->address = address;
	allocation->size = size;
	allocation->page = page;
	return (allocation);
}

t_info	*add_allocation(t_page *page, size_t size)
{
	t_info	*allocation;
	t_info	*curr;

	allocation = 0;
	curr = page->allocations;
	if (page->allocations)
	{
		while (curr && curr->next && (curr->next->address - (curr->address +
															curr->size)) < size)
			curr = curr->next;
		if (curr &&	(curr->next ||
			(curr->page->address + curr->page->size -
			 get_allocation_end(curr)) >= size))
		{
			allocation = allocate_chunk(get_allocation_end(curr), size, page);
			allocation->next = curr->next;
			curr->next = allocation;
		}
	}
	else
	{
		allocation = allocate_chunk(get_page_address(page), size, page);
		page->allocations = allocation;
	}
	return (allocation);
}

void	*get_new_allocation(t_page *page, size_t size)
{
	t_info	*allocation;

	allocation = 0;
	if (!page)
		return (0);
	if (page->empty >= size + sizeof(t_info))
	{
		allocation = add_allocation(page, size + sizeof(t_info));
		if (allocation)
		{
			allocation->page = page;
			page->empty -= allocation->size;
		}
	}
	if (!allocation)
	{
		if (!page->next)
			page->next = get_new_page(page->type, size);
		allocation = get_new_allocation(page->next, size);
	}

	return	(allocation);
}
