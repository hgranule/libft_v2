/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_detach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 05:58:24 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/11 09:20:51 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

unsigned	str_is_detached(const t_string *str)
{
	return (str->f & STR_DETACHED);
}

unsigned	str_detach(t_string *str)
{
	t_area_ptr	new_memory_area;
	unsigned	errcode;

	errcode = STR_OK;
	if (!str_is_detached(str))
	{
		new_memory_area = str_area_alloc(str->sz);
		if (new_memory_area != NULL)
		{
			ft_memcpy(new_memory_area, str->d, str->sz);
			str->f |= STR_DETACHED;
		}
		else
		{
			errcode = STR_ERR_ALLOC;
			str->err = STR_ERR_ALLOC;
		}
		str->d = new_memory_area;
	}
	return (errcode);
}
