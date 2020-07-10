/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 04:34:56 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 07:35:04 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "../util/util.h"

t_string	str_raw(const void *data, size_t offset, size_t len)
{
	t_string	str_new;

	str_new.d = (void *)((size_t)data + offset);
	str_new.err = STR_OK;
	str_new.f = 0;
	str_new.sz = len;
	return (str_new);
}

t_string	str_raw_detach(const void* data, size_t offset, size_t len)
{
	t_string	str_new;

	str_new = str_raw(data, offset, len);
	str_new.err = str_detach(&str_new);
	return (str_new);
}
