//
// Created by Andrew Radiuk on 2019-04-08.
//

#include "ft_malloc.h"

void	free(void *ptr)
{
	if (!ptr)
		return ;

	deallocate((ptrdiff_t)ptr);
}

t_info *find_allocation(ptrdiff_t address, t_info **previous)
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

void deallocate(ptrdiff_t address)
{
	t_page	*page;
	t_info	*previous;
	t_info	*allocation;

	allocation = find_allocation(address, &previous);
	if (!allocation)
		return ;
	page = allocation->page;
	page->empty += allocation->size;
	if (!previous)
		page->allocations = allocation->next;
	else
		previous->next = allocation->next;
	ft_bzero(allocation, sizeof(t_info));
}
