/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ouput_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:23:07 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/10 11:33:57 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	get_allocation_info(t_info *info)
{
	char	*address;

	address = ft_itoa_base(info->address, 16, 'A');
	ft_putstr("0x");
	ft_putstr(address);
	ft_putstr(" - ");
	ft_strdel(&address);
	address = ft_itoa_base((long)(info->address + info->size), 16, 'A');
	ft_putstr("0x");
	ft_putstr(address);
	ft_strdel(&address);
	ft_putstr(" : ");
	ft_putnbr((int)info->size);
	ft_putstr(" bytes\n");
}

void	get_page_info(t_page *page)
{
	char	*address;

	address = 0;
	if (page->type == tiny)
		ft_putstr("TINY");
	else if (page->type == small)
		ft_putstr("SMALL");
	else
		ft_putstr("LARGE");
	address = ft_itoa_base((long)page->address, 16, 'A');
	ft_putstr(" : ");
	ft_putstr("0x");
	ft_putstr(address);
	ft_strdel(&address);
	ft_putstr("\n");
}

void	show_alloc_mem(void)
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
		page = page->next;
	}
	ft_putstr("\n");
}

void	show_alloc_mem_ex(void)
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
			ft_putnbr(allocation->num);
			ft_putstr(": ");
			get_allocation_info(allocation);
			allocation = allocation->next;
		}
		page = page->next;
	}
	ft_putstr("\n");
}
