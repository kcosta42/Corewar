/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_oct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:51:41 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define OCT		"01234567"

static int	pt_oct(unsigned long long nb, t_data *data, int pos, int wmax)
{
	int	i;
	int	pre;

	i = nb ? ft_nblen_b(nb, 8) : 0;
	pre = wmax - i;
	while (pre--)
		addchar(data, '0', data->length + pos++);
	while (i--)
	{
		addchar(data, OCT[nb / ft_power(8, i)], data->length + pos++);
		nb %= ft_power(8, i ? i : 1);
	}
	return (pos);
}

static void	ib_oct(unsigned long long nb, t_form *form, int wmax, t_data *data)
{
	int	pos;

	pos = 0;
	while (pos < data->buff - wmax && !form->minus)
		addchar(data, ' ', data->length + pos++);
	if (form->hash && !form->nul)
	{
		addchar(data, '0', data->length + pos++);
		wmax -= 1;
	}
	pos = pt_oct(nb, data, pos, wmax);
	while (pos < data->buff && form->minus)
		addchar(data, ' ', data->length + pos++);
}

void		fwp_oct(unsigned long nb, t_form *form, t_data *data)
{
	int len;
	int wmax;
	int pre;

	form->zero = form->minus ? 0 : form->zero;
	pre = form->pre >= 0 ? 1 : 0;
	len = form->hash ? ft_nblen_b(nb, 8) + 1 : ft_nblen_b(nb, 8);
	wmax = len >= form->pre ? len : form->pre;
	wmax -= ((!form->pre && !nb) || (form->hash && !nb)) ? 1 : 0;
	wmax = (form->zero && !pre && form->width > wmax) ? form->width : wmax;
	len = wmax < form->width ? form->width : wmax;
	data->buff = len;
	ib_oct(nb, form, wmax, data);
	data->length += len;
}
