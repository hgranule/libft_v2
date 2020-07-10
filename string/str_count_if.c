/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_count_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:45:08 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/12 19:54:11 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"

ssize_t			str_count_if(t_string *str, size_t offset, size_t len,
				ssize_t (*callback)(char c, size_t i))
{
	size_t			index;
	ssize_t			counter;
	const size_t	real_offset = offset > str->sz ? str->sz : offset;
	char *const		str_data = str->d + real_offset;
	const size_t	real_len = len > str->sz - real_offset
					? str->sz - real_offset : len;

	counter = 0;
	index = (size_t)-1;
	while (++index < real_len)
		counter += callback(str_data[index], index + offset);
	return (counter);
}
