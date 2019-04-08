/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:07:48 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/08 15:07:50 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		get_page_size(t_page *page)
{
	return (page->size - sizeof(t_page));
}

ptrdiff_t	get_page_address(t_page *page)
{
	return (page->address + sizeof(t_page));
}

size_t		get_allocation_size(t_info *allocation)
{
	return (allocation->size - sizeof(t_info));
}

ptrdiff_t	get_allocation_address(t_info *allocation)
{
	return (allocation->address + sizeof(t_info));

}

ptrdiff_t	get_allocation_end(t_info *allocation)
{
	return get_allocation_address(allocation) + get_allocation_size(allocation);
}
