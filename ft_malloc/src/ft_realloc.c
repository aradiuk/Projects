/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:23:20 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/10 11:23:21 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*allocation;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (0);
	}
	allocation = get_new_reallocation(ptr, size);
	return (allocation);
}

void	*get_new_reallocation(void *ptr, size_t size)
{
	t_page	*page;
	t_info	*allocation;
	t_info	*tmp;

	allocation = find_allocation((ptrdiff_t)(ptr), &tmp);
	if (!allocation)
		return (0);
	page = allocation->page;
	if ((allocation->next &&
		(size_t)(allocation->next->address -
				get_allocation_address(allocation)) >= size) ||
		(!allocation->next && is_enough_size(page, allocation, size)))
	{
		page->empty -= size - get_allocation_size(allocation);
		allocation->size = size + sizeof(t_info);
		return (ptr);
	}
	return (reallocate_and_move(ptr, size, get_allocation_size(allocation)));
}

size_t	min_size(size_t first, size_t second)
{
	return (first < second ? first : second);
}

void	*reallocate_and_move(void *ptr, size_t size, size_t alloc_size)
{
	void	*allocation;

	allocation = malloc(size);
	if (allocation)
	{
		ft_memmove(allocation, ptr, min_size(size, alloc_size));
		free(ptr);
	}
	return (allocation);
}
