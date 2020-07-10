/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 11:26:40 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/11 09:58:57 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

unsigned		str_append_str(t_string *str, const t_string *appendix)
{
	const size_t		area_size = str->sz + appendix->sz;
	t_area_ptr			area;

	if (appendix->sz == 0)
		return (STR_OK);
	area = (area_size <= str_capacity(str)) ? str->d : str_area_alloc(area_size);
	if (area == NULL)
		return (str->err = STR_ERR_ALLOC);
	ft_memmove(area, str->d, str->sz);
	ft_memmove(area + str->sz, appendix->d, appendix->sz);
	if (str_is_detached(str) && area != str->d)
		str_area_dealloc(str->d);
	str->d = area;
	str->sz = area_size;
	str->f |= STR_DETACHED;
	return (STR_OK);
}

unsigned		str_append_cstr(t_string *str, const char *appendix)
{
	const t_string	appx = str_new_cstr(appendix);

	return (str_append_str(str, &appx));
}
