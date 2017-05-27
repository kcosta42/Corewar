/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:52:00 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define NUM		"0123456789"

static int	print_num(long long nb, t_form *form, t_data *data, int i)
{
	int	nblen;

	nblen = (!nb && form->pre == 0) ? 0 : ft_nblen(nb);
	while (nblen--)
	{
		addchar(data, nb > 0 ? NUM[nb / ft_power(10, nblen)]
			: NUM[(nb / ft_power(10, nblen)) * -1], data->length + i++);
		nb %= ft_power(10, nblen ? nblen : 1);
		if (form->apo && nblen % 3 == 0)
			addchar(data, ',', data->length + i++);
	}
	return (i);
}

static void	ib_int(long long nb, t_form *form, int wmax, t_data *data)
{
	int pos;
	int	nblen;
	int	fill;

	pos = 0;
	nblen = (!nb && form->pre == 0) ? 0 : ft_nblen(nb);
	nblen += form->apo ? (ft_nblen(nb) - 1) / 3 : 0;
	while (pos < data->buff - wmax && !form->minus)
		addchar(data, ' ', data->length + pos++);
	if (nb < 0 || form->plus || form->space)
	{
		fill = form->plus ? '+' : ' ';
		fill = nb < 0 ? '-' : fill;
		addchar(data, fill, data->length + pos++);
		wmax--;
	}
	while (pos < data->buff - nblen && (wmax-- - nblen) > 0)
		addchar(data, '0', data->length + pos++);
	pos = print_num(nb, form, data, pos);
	while (pos < data->buff)
		addchar(data, ' ', data->length + pos++);
}

void		fwp_int(long long nb, t_form *form, t_data *data)
{
	int len;
	int wmax;

	if (form->apo)
		form->apo = (ft_nblen(nb) - 1) / 3;
	form->preflag = form->pre >= 0 ? 1 : 0;
	wmax = ft_nblen(nb) >= form->pre ? ft_nblen(nb) : form->pre;
	wmax += (nb < 0 || form->plus || form->space) ? 1 : 0;
	wmax += form->apo ? form->apo : 0;
	len = wmax < form->width ? form->width : wmax;
	len -= (nb == 0 && form->pre == 0 && !form->width) ? 1 : 0;
	wmax = (form->zero && form->pre == -1 && !form->minus) ? len : wmax;
	wmax -= (!nb && form->pre == 0) ? 1 : 0;
	data->buff = len;
	ib_int(nb, form, wmax, data);
	data->length += len;
}
