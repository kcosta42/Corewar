/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_power.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 17:36:58 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/19 17:37:18 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long int	ft_u_power(int n, unsigned int p)
{
	unsigned long int nb;

	nb = 1;
	while (p-- != 0)
		nb *= n;
	return (nb);
}
