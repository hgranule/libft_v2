/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 11:26:40 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/11 11:50:23 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

unsigned		str_replace_str(t_string *str, const t_string *portion,
				size_t pos, size_t len)
{
	const size_t	r_pos = pos > str->sz ? str->sz : pos;
	const size_t	max_len = str->sz - r_pos;
	const size_t	r_len = len > max_len ? max_len : len;
	const size_t	full_size = str->sz - r_len + portion->sz;
	t_area_ptr		area;

	if (r_len == 0 && portion->sz == 0)
		return (STR_OK);
	area = !str_is_detached(str)
		|| str_size_to_blocks(full_size) != str_area_blocks(str->d)
		? str_area_alloc(full_size) : str->d;
	if (area == NULL)
		return (str->err = STR_ERR_ALLOC);
	ft_memmove(area,
		str->d, r_pos);
	ft_memmove(area + r_pos + portion->sz,
		str->d + r_pos + r_len, str->sz - (r_pos + r_len));
	ft_memmove(area + r_pos,
		portion->d, portion->sz);
	if (area != str->d && str_is_detached(str))
		str_area_dealloc(str->d);
	str->d = area;
	str->f |= STR_DETACHED;
	str->sz = full_size;
	return (STR_OK);
}

unsigned		str_replace_cstr(t_string *str, const char *portion,
				size_t pos, size_t len)
{
	const t_string	portion_s = str_new_cstr(portion);

	return (str_replace_str(str, &portion_s, pos, len));
}