/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:03:49 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/22 16:17:35 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int		reverse_byte_32(unsigned int num)
{
	unsigned int		reverse;

	reverse = 0x000000FF & num;
	reverse = (reverse << 8) + ((0x0000FF00 & num) >> 8);
	reverse = (reverse << 8) + ((0x00FF0000 & num) >> 16);
	reverse = (reverse << 8) + ((0xFF000000 & num) >> 24);
	return (reverse);
}

static unsigned short	reverse_byte_16(unsigned int num)
{
	unsigned short		reverse;

	reverse = 0x00FF & num;
	reverse = (reverse << 8) + ((0xFF00 & num) >> 8);
	return (reverse);
}

ssize_t					fixed_write(int fildes, const void *buf, size_t nbyte)
{
	unsigned int		fixed;

	if (nbyte == 4)
		fixed = reverse_byte_32(*(unsigned int*)buf);
	else if (nbyte == 2)
		fixed = reverse_byte_16(*(unsigned int*)buf);
	else
		fixed = *(unsigned int*)buf;
	return (write(fildes, &fixed, nbyte));
}

unsigned int			fixed_read_32(int fildes)
{
	unsigned int		args_i;

	read(fildes, &args_i, 4);
	return (reverse_byte_32(args_i));
}

unsigned short			fixed_read_16(int fildes)
{
	unsigned short		args_s;

	read(fildes, &args_s, 2);
	return (reverse_byte_16(args_s));
}
