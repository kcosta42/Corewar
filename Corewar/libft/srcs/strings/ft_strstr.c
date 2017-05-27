/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 07:54:34 by bduron            #+#    #+#             */
/*   Updated: 2017/04/22 14:50:57 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t len;

	len = ft_strlen(little);
	if (*little == 0)
		return ((char *)big);
	while (*big)
	{
		if (*big == *little && ft_strncmp(big, little, len) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
