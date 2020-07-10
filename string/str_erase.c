/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_erase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:03:09 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/11 10:39:32 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

unsigned		str_erase(t_string *str, size_t offset, size_t len)
{
	const size_t	max_len = str->sz - offset;
	const size_t	real_len = len > max_len ? max_len : len;
	const size_t	full_size = str->sz - real_len;
	const size_t	post_pos = offset + real_len;
	t_area_ptr		area;

	if (offset > str->sz || real_len == 0)
		return (STR_OK);
	area = !str_is_detached(str)
		|| str_size_to_blocks(full_size) != str_area_blocks(str->d)
		? str_area_alloc(full_size) : str->d;
	if (area == NULL)
		return (str->err = STR_ERR_ALLOC);
	ft_memmove(area, str->d, offset);
	ft_memmove(area + offset, str->d + post_pos, full_size - offset);
	if (area != str->d && str_is_detached(str))
		str_area_dealloc(str->d);
	str->d = area;
	str->f |= STR_DETACHED;
	str->sz = full_size;
	return (STR_OK);
}
