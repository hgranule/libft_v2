/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:40:18 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/12 19:12:59 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"

void			str_map(t_string *str, size_t offset, size_t len,
				char (*callback)(char c, size_t i))
{
	const size_t	real_offset = offset > str->sz ? str->sz : offset;
	const size_t	max_len = str->sz - real_offset;
	const size_t	real_len = len > max_len ? max_len : len;
	char			*str_data;
	size_t			index;

	if (real_len)
		str_detach(str);
	str_data = str->d + real_offset;
	if (str->err != STR_ERR_ALLOC)
	{
		index = (size_t)-1;
		while (++index < real_len)
			str_data[index] = callback(str_data[index], index + offset);
	}
}
