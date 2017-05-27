/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:46:16 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:32:42 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	signed_cast(long long val, int mod)
{
	if (mod == LL)
		val = (long long)val;
	else if (mod == L)
		val = (long)val;
	else if (mod == HH)
		val = (char)val;
	else if (mod == H)
		val = (short)val;
	else if (mod == J)
		val = (intmax_t)val;
	else if (mod == Z)
		val = (size_t)val;
	else if (mod == -1)
		val = (int)val;
	return (val);
}

long long	unsigned_cast(long long val, int mod)
{
	if (mod == LL)
		val = (unsigned long long)val;
	else if (mod == L)
		val = (unsigned long)val;
	else if (mod == HH)
		val = (unsigned char)val;
	else if (mod == H)
		val = (unsigned short)val;
	else if (mod == J)
		val = (uintmax_t)val;
	else if (mod == Z)
		val = (size_t)val;
	else if (mod == -1)
		val = (unsigned int)val;
	return (val);
}
