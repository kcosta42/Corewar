/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:34:49 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:11 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		lenstr;
	const char	*b;
	size_t		l;

	l = len;
	b = big;
	lenstr = ft_strlen(little);
	if (*little == 0)
		return ((char *)big);
	while (*big && len)
	{
		if ((big - b + lenstr) <= l && *big == *little
				&& ft_strncmp(big, little, lenstr) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
