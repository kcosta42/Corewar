/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:51:24 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define HEX        "0123456789ABCDEF"
#define LHEX       "0123456789abcdef"

static int	pt_hex(unsigned long long nb, t_data *data, int pos, int wmax)
{
	int	i;
	int	pre;

	i = nb ? ft_nblen_b(nb, 16) : 0;
	pre = wmax - i;
	while (pre--)
		addchar(data, '0', data->length + pos++);
	while (i--)
	{
		addchar(data, data->field == 'x' ? LHEX[nb / ft_power(16, i)] :
				HEX[nb / ft_power(16, i)], data->length + pos++);
		nb %= ft_power(16, i ? i : 1);
	}
	return (pos);
}

static void	ib_hex(unsigned long long nb, t_form *form, int wmax, t_data *data)
{
	int	pos;

	pos = 0;
	while (pos < data->buff - wmax && !form->minus)
		addchar(data, ' ', data->length + pos++);
	if (form->hash && !form->nul)
	{
		addchar(data, '0', data->length + pos++);
		addchar(data, data->field == 'x' ? 'x' : 'X', data->length + pos++);
		wmax -= 2;
	}
	pos = pt_hex(nb, data, pos, wmax);
	while (pos < data->buff && form->minus)
		addchar(data, ' ', data->length + pos++);
}

void		fwp_hex(unsigned long long nb, t_form *form, t_data *data)
{
	int len;
	int wmax;

	form->preflag = form->pre >= 0 ? 1 : 0;
	form->nul = !nb ? 1 : 0;
	wmax = ft_nblen_b(nb, 16) >= form->pre ? ft_nblen_b(nb, 16) : form->pre;
	wmax += (form->hash && nb) ? 2 : 0;
	len = wmax < form->width ? form->width : wmax;
	len -= (!form->pre && !nb && !form->width) ? 1 : 0;
	data->buff = len;
	wmax = (form->zero && form->pre == -1 && !form->minus) ? len : wmax;
	wmax -= (!nb && form->pre == 0) ? 1 : 0;
	ib_hex(nb, form, wmax, data);
	data->length += len;
}
