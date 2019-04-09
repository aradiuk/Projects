//
// Created by Andrew Radiuk on 2019-04-08.
//

#include "ft_malloc.h"

size_t	max_size(size_t first, size_t second)
{
	return first > second ? first : second;
}

size_t	get_size(t_type type)
{
	if (type == tiny)
		return (TINY);
	else if (type == small)
		return (SMALL);
	else
		return (LARGE);
}

t_page	*create_new_page(t_type type, size_t in_size)
{
	t_page	*page;
	size_t	size;
	void	*address;
	int		page_size;

	size = get_size(type);
	size = (size + sizeof(t_info)) * ((type < large) ? MMAP_COEF : 1);
	size = max_size(size, in_size + sizeof(t_info)) + sizeof(t_page);
	page_size = getpagesize();
	if (size % page_size)
		size += page_size - (size % page_size);
	address = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (address == MAP_FAILED)
		return (0);
	ft_bzero(address, sizeof(t_page));
	page = (t_page *)address;
	page->address = (ptrdiff_t)address;
	page->size = size;
	page->type = type;
	page->empty = get_page_size(page);
	return (page);
}

t_page	*get_new_page(t_type type, size_t size)
{
	t_page	*page;
	t_page	*curr;

	page = create_new_page(type, size);
	curr = g_pages;
	if (!curr)
		g_pages = page;
	else if (curr->type > type)
	{
		g_pages = page;
		page->next = curr;
	}
	else
	{
		while (curr->next && curr->next->type <= page->type)
			curr = curr->next;
		page->next = curr->next;
		curr->next = page;
	}
	return (page);
}

t_page	*get_page(t_type type, size_t size)
{
	t_page	*page;

	page = g_pages;
	while (page)
	{
		if (page->type == type)
			break;
		page = page->next;
	}
	if (!page)
		page = get_new_page(type, size);
	return (page);
}