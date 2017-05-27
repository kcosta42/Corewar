/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:52:09 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define HEX	"0123456789abcdef"

static int	pt_ptr(unsigned long ptr, t_data *data, int pos)
{
	int	i;

	i = ptr ? ft_nblen_b(ptr, 16) : 0;
	while (i--)
	{
		addchar(data, HEX[ptr / ft_power(16, i)], data->length + pos++);
		ptr %= ft_power(16, i ? i : 1);
	}
	return (pos);
}

static void	ib_ptr(unsigned long ptr, t_form *form, int wmax, t_data *data)
{
	int	i;
	int pos;

	pos = 0;
	i = ptr ? ft_nblen_b(ptr, 16) : 0;
	while (pos < data->buff - wmax && !form->minus)
		addchar(data, ' ', data->length + pos++);
	addchar(data, '0', data->length + pos++);
	addchar(data, 'x', data->length + pos++);
	wmax -= 2;
	while (wmax-- > i)
		addchar(data, '0', data->length + pos++);
	pos = pt_ptr(ptr, data, pos);
	wmax -= i;
	while (pos < data->buff)
		addchar(data, ' ', data->length + pos++);
}

void		fwp_ptr(unsigned long ptr, t_form *form, t_data *data)
{
	int wmax;
	int len;

	data->buff = ptr ? ft_nblen_b(ptr, 16) : 1;
	wmax = data->buff >= form->pre ? data->buff + 2 : form->pre + 2;
	wmax -= (!ptr && form->pre == 0) ? 1 : 0;
	data->buff = wmax < form->width ? form->width : wmax;
	wmax = form->zero ? data->buff : wmax;
	len = data->buff;
	ib_ptr(ptr, form, wmax, data);
	data->length += len;
}
