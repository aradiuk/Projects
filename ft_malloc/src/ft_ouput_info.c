//
// Created by Andrew Radiuk on 2019-04-08.
//

#include "ft_malloc.h"

void	get_allocation_info(t_info *info)
{
	char	*address;

	address = ft_itoa_base(info->address, 16, 'A');
	ft_putstr(address);
	ft_putstr(" - ");
	ft_strdel(&address);
	address = ft_itoa_base(info->address + info->size, 16, 'A');
	ft_putstr(address);
	ft_putstr(" : ");
	ft_putnbr((int)info->size);
	ft_putstr(" bytes\n");
}

void	get_page_info(t_page *page)
{
	char	*type;
	char	*address;

	if (page->type == tiny)
		type = ft_strdup("TINY");
	else if (page->type == small)
		type = ft_strdup("SMALL");
	else
		type = ft_strdup("LARGE");
	address = ft_itoa_base(page->address, 16, 'A');
	ft_putstr(type);
	ft_putstr(" : ");
	ft_putstr(address);
	ft_strdel(&type);
	ft_strdel(&address);
}

void	show_alloc_mem()
{
	t_page	*page;
	t_info	*allocation;

	page = g_pages;
	while (page)
	{
		get_page_info(page);
		allocation = page->allocations;
		while (allocation)
		{
			get_allocation_info(allocation);
			allocation = allocation->next;
		}
	}
	ft_putstr("\n");
}
