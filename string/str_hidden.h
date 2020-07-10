/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_hidden.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 01:29:41 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 07:03:50 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_HIDDEN_H
# define STR_HIDDEN_H

# include "str.h"

# define STR_BLK_SIZE 0x40

enum			e_str_flags
{
	STR_DETACHED = 0b1
};

/*
** Pointer points to a shifted address of allocated area.
** Real begin of this area located at [memory_area_ptr - @sizeof(size_t)],
** because these bytes have blocks amount value of type size_t inside them.
*/
typedef void*	t_area_ptr;

/*
** Allocate memory in blocks, and write blocks amount to
** first @sizeof(size_t) bytes of that memory.
**
** Returns allocated shifted memory address (adr + sizeof(size_t)])
** or NULL if allocation failed.
*/
t_area_ptr		str_area_alloc(size_t sz);

/*
** Returns blocks value from t_string::d address.
*/
size_t			str_area_blocks(t_area_ptr memory_area);

/*
** Deallocates memory area.
**
*/
void			str_area_dealloc(t_area_ptr memory_area);

/*
** Allocates new area and copies from @data as much bytes as it can.
**
** If allocation fails, returns NULL.
*/
t_area_ptr		str_area_ncopy(void *data, size_t old_sz, size_t nw_sz);

/*
** Calculates how many blocks needed for location of @size bytes.
*/
size_t			str_size_to_blocks(size_t size);

#endif
