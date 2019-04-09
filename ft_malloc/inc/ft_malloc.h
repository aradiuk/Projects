/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:19:42 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/08 14:20:02 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <stddef.h>
# include "libft.h"

# define TINY 512
# define SMALL 2048
# define LARGE 2048 * 5
# define MMAP_COEF 100

typedef enum	e_type
{
	tiny,
	small,
	large
}				t_type;

typedef struct	s_page
{
	ptrdiff_t		address;
	size_t			size;
	size_t			empty;
	t_type			type;
	struct s_page	*next;
	struct s_info	*allocations;
}				t_page;

typedef struct	s_info
{
	ptrdiff_t		address;
	size_t			size;
	t_page			*page;
	struct s_info	*next;
}				t_info;

extern t_page *g_pages;

void		*malloc(size_t size);
void		*get_new_allocation(t_page *page, size_t size);
t_info		*add_allocation(t_page *page, size_t size);
t_info		*allocate_chunk(ptrdiff_t address, size_t size, t_page *page);
void		free(void *ptr);
t_info		*find_allocation(ptrdiff_t address, t_info **previous);
void		deallocate(ptrdiff_t address);
void		*realloc(void *ptr, size_t size);
void		*get_new_reallocation(void *ptr, size_t size);
void		*reallocate_and_move(void *ptr, size_t size, size_t alloc_size);
t_page		*get_page(t_type type, size_t size);
t_page		*get_new_page(t_type type, size_t size);
t_page		*create_new_page(t_type type, size_t size);
size_t		get_size(t_type type);
void		show_alloc_mem();
void		get_page_info(t_page *page);
size_t		get_page_size(t_page *page);
ptrdiff_t	get_page_address(t_page *page);
size_t		get_allocation_size(t_info *allocation);
ptrdiff_t	get_allocation_address(t_info *allocation);
ptrdiff_t	get_allocation_end(t_info *allocation);

#endif
