/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:55:16 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:35:08 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	s = src;
	d = dst;
	if (len == 0 || src == dst)
		return (dst);
	if (src > dst)
		while (len--)
			*d++ = *s++;
	if (src < dst)
		while (len)
		{
			*(d + len - 1) = *(s + len - 1);
			len--;
		}
	return (dst);
}
