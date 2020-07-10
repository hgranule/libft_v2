/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:46:48 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/11 10:01:53 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

size_t			str_find_str(const t_string *str, const t_string *substr,
				size_t offset, size_t n)
{
	const size_t	real_offset = offset > str->sz ? str->sz : offset;
	const size_t	max_n = str->sz - real_offset;
	const size_t	real_n = n > max_n ? max_n : n;
	const void		*needle = ft_memmem(str->d + real_offset, real_n,
					substr->d, substr->sz);

	if (!needle)
		return (STR_NPOS);
	return ((size_t)needle - (size_t)str->d);
}

size_t			str_find_cstr(const t_string *str, const char *substr,
				size_t offset, size_t n)
{
	const t_string	sub = str_new_cstr(substr);

	return (str_find_str(str, &sub, offset, n));
}

size_t			str_find_ch(const t_string *str, int c,
				size_t offset, size_t n)
{
	const size_t	real_offset = offset > str->sz ? str->sz : offset;
	const size_t	max_n = str->sz - real_offset;
	const size_t	real_n = n > max_n ? max_n : n;
	const void		*needle = ft_memchr(str->d + real_offset, c, real_n);

	if (!needle)
		return (STR_NPOS);
	return ((size_t)needle - (size_t)str->d);
}
