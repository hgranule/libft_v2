/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 06:35:07 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 07:35:10 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"

void	str_delete(t_string *str)
{
	if (str_is_detached(str))
		str_area_dealloc(str->d);
	str->d = NULL;
	str->err = STR_OK;
	str->sz = 0;
	str->f = 0;
}
