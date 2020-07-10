/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_area.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 04:36:37 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 07:32:02 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"
#include <stdlib.h>

inline static size_t	*get_allocation_address(t_area_ptr memory_area)
{
	return ((size_t *)memory_area - 1);
}

t_area_ptr				str_area_alloc(size_t n)
{
    const size_t		blocks = str_size_to_blocks(n);
    size_t *const		memory = malloc(blocks * STR_BLK_SIZE);
	const t_area_ptr	area = memory + (memory != NULL);

	if (memory != NULL)
		memory[0] = blocks;
	return (area);
}

void					str_area_dealloc(t_area_ptr memory_area)
{
	free(get_allocation_address(memory_area));
}

t_area_ptr				str_area_ncopy(void *old, size_t old_sz,
						size_t nw_sz)
{
	const size_t		min_sz = old_sz < nw_sz ? old_sz : nw_sz;
	const t_area_ptr	area = str_area_alloc(nw_sz);

	if (area)
		ft_memcpy(area, old, min_sz);
	return (area);
}
