/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_page.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:23:13 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/16 18:46:56 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		check_page_for_emptiness(t_page *page)
{
	t_page	*curr;

	curr = g_pages;
	if (page->allocations != 0)
		return (0);
	while (curr)
	{
		if (curr->type == page->type || page->type == large)
			return (1);
		curr = curr->next;
	}
	return (0);
}

size_t	get_size(t_type type, size_t in_size)
{
	size_t	size;

	size = 0;
	if (type == tiny)
		size = (sizeof(t_info) + TINY) * ALLOCS;
	else if (type == small)
		size = (sizeof(t_info) + SMALL) * ALLOCS;
	else
		size = sizeof(t_info) + in_size;
	size += sizeof(t_page);
	return (size);
}

t_page	*create_new_page(t_type type, size_t in_size)
{
	t_page	*page;
	size_t	size;
	void	*address;
	int		page_size;

	size = get_size(type, in_size);
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
	if (!g_pages)
	{
        g_pages = page;
        return (page);
	}
	curr = g_pages;
	if (g_pages->type > type)
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

	if (type == large)
	    return (get_new_page(type, size));
	page = g_pages;
	while (page)
	{
		if (page->type == type)
			break ;
		page = page->next;
	}
	if (!page)
		page = get_new_page(type, size);
	return (page);
}
