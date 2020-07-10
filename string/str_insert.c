/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 08:02:38 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/11 09:56:28 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

unsigned		str_insert_str(t_string *str, const t_string *ins, size_t pos)
{
	const size_t	real_pos = pos > str->sz ? str->sz : pos;
	const size_t	post_size = str->sz - real_pos;
	const size_t	post_pos = real_pos + ins->sz;
	const size_t	full_size = ins->sz + str->sz;
	t_area_ptr		area;

	if (ins->sz == 0)
		return (STR_OK);
	area = str_capacity(str) < full_size ? str_area_alloc(full_size) : str->d;
	if (area == NULL)
		return (str->err = STR_ERR_ALLOC);
	ft_memmove(area, str->d, real_pos);
	ft_memmove(area + post_pos, str->d + real_pos, post_size);
	ft_memmove(area + real_pos, ins->d, ins->sz);
	if (area != str->d && str_is_detached(str))
		str_area_dealloc(str->d);
	str->d = area;
	str->f |= STR_DETACHED;
	str->sz = full_size;
	return (STR_OK);
}

unsigned		str_insert_cstr(t_string *str, const char *ins, size_t pos)
{
	const t_string	insertion = str_new_cstr(ins);

	return str_insert_str(str, &insertion, pos);
}
