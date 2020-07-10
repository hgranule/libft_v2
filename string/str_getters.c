/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:15:17 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 06:54:26 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"

unsigned		str_get_errcode(const t_string *str)
{
	return (str->err);
}

size_t			str_len(const t_string *str)
{
	return (str->sz);
}

char			*str_data(t_string *str)
{
	return (str->d);
}

size_t			str_capacity(const t_string *str)
{
	if (str_is_detached(str))
		return (str_area_blocks(str->d) * STR_BLK_SIZE - sizeof(size_t) - 1);
	return (str->sz);
}
