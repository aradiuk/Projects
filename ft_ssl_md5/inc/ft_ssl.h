/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:25:53 by aradiuk           #+#    #+#             */
/*   Updated: 2019/04/08 11:25:54 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_ssl_md5.h"
# include "ft_ssl_sha256.h"

# define MAX_FLAGS_IT 5

typedef enum	e_flag_type
{
	print,
	quiet,
	reverse,
	string,
	file
}				t_flag_type;

typedef struct	s_flags
{
	int		is_initialised;
	char	*string_or_file;
	char	*checksum;
	char	*add;
	char	*flag_text;
}				t_flags;

void			error_found(char *error_text);
void			initial_flags(t_flags *flags);
void			clean_memory(t_flags *flags, t_list **invalid_args);
void			parse_input(int argc, char **argv, t_flags *flags,
							t_list **invalid_args);
void			init_flag(t_flag_type flag_type, char *text, t_flags *flags,
							t_list **invalid_args);
void			try_md5(t_flags *flags);
void			try_sha256(t_flags *flag);
void			try_sha224(t_flags *flags);
char			*read_data(int fd);
void			ft_ssl_md5_checksum(const char *str, t_flags *flag);
void			ft_ssl_sha256_checksum(const char *str, t_flags *flag);
void			ft_ssl_sha224_checksum(const char *str, t_flags *flag);
void			print_results(t_flags *flags);
void			prepare_file_and_string(t_flags *flags, char **file_add,
							char **string_add);
void			print_file_and_string(t_flags *flags, char *file_add,
							char *string_add);
void			print_invalid_args(t_list *invalid_arg);
void			wrong_input();

#endif
