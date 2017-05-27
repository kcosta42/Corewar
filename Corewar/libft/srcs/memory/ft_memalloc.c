/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:16:12 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:35:08 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *s;

	if (!size)
		return (NULL);
	s = malloc(size);
	if (!s)
		return (NULL);
	if (!ft_memset(s, 0, size))
		return (NULL);
	return (s);
}
