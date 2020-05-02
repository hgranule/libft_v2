/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <wp3d3p@yandex.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 19:23:56 by hgranule          #+#    #+#             */
/*   Updated: 2020/07/05 23:43:35 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDFT_H
# define STDFT_H

# include <stddef.h>

void	*ft_memchr(const void *mem, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memset(void *mem, int c, size_t len);
int		ft_memcmp(const void *m1, const void *m2, size_t len);
size_t	ft_strlen(const char *str);

#endif
