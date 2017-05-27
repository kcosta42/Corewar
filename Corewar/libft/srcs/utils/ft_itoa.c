/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 08:38:48 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:22 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*s;
	int				i;
	unsigned int	nb;
	int				sign;

	sign = n;
	nb = n < 0 ? -n : n;
	i = 2 + (n < 0);
	while (n /= 10)
		i++;
	if (!(s = (char *)malloc(sizeof(char) * i--)))
		return (NULL);
	s[i--] = '\0';
	s[i--] = nb % 10 + '0';
	while (nb /= 10)
		s[i--] = nb % 10 + '0';
	if (sign < 0)
		*s = '-';
	return (s);
}
