/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 09:50:52 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/10 11:15:10 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include "../util/util.h"

t_string		str_substr(const t_string *str, size_t offset, size_t len)
{
	const size_t	real_offset = offset > str->sz ? str->sz : offset;
	const size_t	max_len = str->sz - real_offset;
	const size_t	real_len = max_len <= len ? max_len : len;


	return (str_raw(str->d, real_offset, real_len));
}

t_string		str_substr_cstr(const char *str, size_t offset, size_t len)
{
	const size_t	cstr_len = ft_strlen(str);
	const size_t	real_offset = offset > cstr_len ? cstr_len : offset;
	const size_t	max_len = cstr_len - offset;
	const size_t	real_len = max_len <= len ? max_len : len;

	return (str_raw(str, real_offset, real_len));
}
