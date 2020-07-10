/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_area_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 06:59:52 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 08:04:01 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"
#include <stdlib.h>

inline static size_t	*get_allocation_address(t_area_ptr memory_area)
{
	return ((size_t *)memory_area - 1);
}

size_t					str_area_blocks(t_area_ptr memory_area)
{
	return (*get_allocation_address(memory_area));
}

size_t					str_size_to_blocks(size_t size)
{
	return ((size + sizeof(size_t)) / STR_BLK_SIZE + 1);
}