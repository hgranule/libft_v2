/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 18:41:40 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 19:45:05 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void		*ft_memmem(const void *big, size_t big_sz,
			const void *little, size_t little_sz)
{
	const char	little_f_sym = *((char *)little);
	void		*ptr;

	if (little_sz == 0 || big_sz == 0)
		return (NULL);
	while (1)
	{
		ptr = ft_memchr(big, little_f_sym, big_sz);
		big_sz -= ptr - big;
		if (!ptr || little_sz > big_sz--)
			return (NULL);
		if (!ft_memcmp(ptr, little, little_sz))
			break ;
		big = ptr + 1;
	}
	return (ptr);
}
