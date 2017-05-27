/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:09:29 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/19 17:54:06 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nblen_b(unsigned long long nb, int base)
{
	int len;

	len = 1;
	if (!base)
		return (0);
	while (nb >= (unsigned int)base)
	{
		nb /= base;
		len++;
	}
	return (len);
}
