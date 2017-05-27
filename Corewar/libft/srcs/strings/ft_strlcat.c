/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:31:40 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:11 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int			n;
	char		*d;
	char const	*s;
	size_t		destlen;

	d = dst;
	s = src;
	n = size;
	while (n-- && *d)
		d++;
	destlen = d - dst;
	if (size == destlen)
		return (destlen + ft_strlen(src));
	while (n-- && *s)
		*d++ = *s++;
	*d = '\0';
	return (destlen + ft_strlen(src));
}
