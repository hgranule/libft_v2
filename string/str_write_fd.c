/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_write_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <hganule@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:09:57 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/07 17:13:13 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str_hidden.h"
#include <unistd.h>

ssize_t		str_write_fd(const t_string *str, int fd)
{
	return (write(fd, str->d, str->sz));
}
