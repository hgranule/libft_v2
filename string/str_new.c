/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 04:03:16 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 07:21:10 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "../util/util.h"

t_string	str_new_empty(void)
{
	return (str_raw("", 0, 0));
}

t_string	str_new_str(const t_string *str)
{
	return (str_raw(str->d, 0, str->sz));
}

t_string	str_new_cstr(const char *cstr)
{
	return (str_raw(cstr, 0, ft_strlen(cstr)));
}


