//
// Created by Andrew Radiuk on 2019-04-08.
//

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
		(!allocation->next &&
		(size_t)(get_page_address(page) + get_page_size(page) -
				get_allocation_end(allocation)) >= size))
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

	if ((allocation = malloc(size)))
	{
		ft_memmove(allocation, ptr, min_size(size, alloc_size));
		free(ptr);
	}
	return (allocation);
}
