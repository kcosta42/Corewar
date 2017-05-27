/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:53:51 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define NUM		"0123456789"

static int	pt_u_num(unsigned long long nb, t_form *form, t_data *data, int i)
{
	int	nblen;

	nblen = (!nb && form->pre == 0) ? 0 : ft_u_nblen(nb);
	while (nblen--)
	{
		addchar(data, nb > 0 ? NUM[nb / ft_u_power(10, nblen)]
			: NUM[(nb / ft_u_power(10, nblen)) * -1], data->length + i++);
		nb %= ft_u_power(10, nblen ? nblen : 1);
		if (form->apo && nblen % 3 == 0)
			addchar(data, ',', data->length + i++);
	}
	return (i);
}

static void	u_int(unsigned long long nb, t_form *form, int wmax, t_data *data)
{
	int i;
	int	nblen;

	i = 0;
	nblen = (!nb && form->pre == 0) ? 0 : ft_u_nblen(nb);
	nblen += form->apo ? (ft_u_nblen(nb) - 1) / 3 : 0;
	while (i < data->buff - wmax && !form->minus)
		addchar(data, ' ', data->length + i++);
	while (i < data->buff - nblen && (wmax-- - nblen) > 0)
		addchar(data, '0', data->length + i++);
	i = pt_u_num(nb, form, data, i);
	while (i < data->buff)
		addchar(data, ' ', data->length + i++);
}

void		fwp_u_int(unsigned long long nb, t_form *form, t_data *data)
{
	int len;
	int wmax;

	if (form->apo)
		form->apo = (ft_u_nblen(nb) - 1) / 3;
	form->preflag = form->pre >= 0 ? 1 : 0;
	wmax = ft_nblen_b(nb, 10) >= form->pre ?
		ft_nblen_b(nb, 10) : form->pre;
	wmax += form->apo ? form->apo : 0;
	len = wmax < form->width ? form->width : wmax;
	len -= (nb == 0 && form->pre == 0 && !form->width) ? 1 : 0;
	wmax = (form->zero && form->pre == -1 && !form->minus) ? len : wmax;
	wmax -= (!nb && form->pre == 0) ? 1 : 0;
	data->buff = len;
	u_int(nb, form, wmax, data);
	data->length += len;
}
