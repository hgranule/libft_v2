/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_resizing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 06:04:37 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 08:11:55 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

unsigned			str_reserve(t_string *str, size_t new_size)
{
	const size_t	old_size = str_capacity(str);
	t_area_ptr		area;

	if (new_size > old_size)
	{
		area = str_area_ncopy(str->d, old_size, new_size);
		if (area == NULL)
			return (str->err = STR_ERR_ALLOC);
		if (str_is_detached(str))
			str_area_dealloc(str->d);
		str->d = area;
		str->f |= STR_DETACHED;
	}
	return (STR_OK);
}

static inline int	capacity_can_handle(size_t capacity, size_t new_sz)
{
	return (str_size_to_blocks(capacity) == str_size_to_blocks(new_sz));
}

unsigned			str_resize(t_string *str, size_t new_len, int c)
{
	const size_t	old_size = str_capacity(str);
	const size_t	old_len = str->sz;
	const int		is_detached = str_is_detached(str);
	t_area_ptr		area;

	if (new_len == old_len)
		return (STR_OK);
	area = capacity_can_handle(old_size, new_len) && is_detached ?
		str->d : str_area_ncopy(str->d, old_size, new_len);
	if (area == NULL)
		return (str->err = STR_ERR_ALLOC);
	if (new_len > old_len)
		ft_memset(area + old_len, c, new_len - old_len);
	if (str->d != area && is_detached)
		str_area_dealloc(str->d);
	str->d = area;
	str->sz = new_len;
	str->f |= STR_DETACHED;
	return (STR_OK);
}

unsigned			str_relenght(t_string *str, size_t new_len, int c)
{
	const size_t	old_len = str->sz;

	if (STR_ERR_ALLOC == str_reserve(str, new_len))
		return (STR_ERR_ALLOC);
	if (new_len > old_len)
		ft_memset(str->d + old_len, c, new_len - old_len);
	str->sz = new_len;
	return (STR_OK);
}
