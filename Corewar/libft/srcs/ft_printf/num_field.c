/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:21:02 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 12:57:26 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_uns_int(va_list ap, t_form *form, t_data *data)
{
	unsigned long long	nb;

	form->pre = form->preflag ? -1 : form->pre;
	if (data->field == 'U')
		form->length = L;
	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		nb = va_arg(data->ap_svg, unsigned long);
	}
	else
		nb = va_arg(ap, unsigned long);
	nb = unsigned_cast(nb, form->length);
	fwp_u_int(nb, form, data);
	data->field = 0;
	return (0);
}

int		print_bin(va_list ap, t_form *form, t_data *data)
{
	unsigned long	nb;

	form->pre = form->preflag ? -1 : form->pre;
	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		nb = va_arg(data->ap_svg, unsigned long);
	}
	else
		nb = va_arg(ap, unsigned long);
	nb = unsigned_cast(nb, form->length);
	fwp_bin(nb, form, data);
	data->field = 0;
	return (0);
}

int		print_int(va_list ap, t_form *form, t_data *data)
{
	long long	nb;

	form->pre = form->preflag ? -1 : form->pre;
	if (data->field == 'D')
		form->length = L;
	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		nb = va_arg(data->ap_svg, long long);
	}
	else
		nb = va_arg(ap, long long);
	nb = signed_cast(nb, form->length);
	fwp_int(nb, form, data);
	data->field = 0;
	return (0);
}

int		print_oct(va_list ap, t_form *form, t_data *data)
{
	unsigned long	nb;

	form->pre = form->preflag ? -1 : form->pre;
	if (data->field == 'O')
		form->length = L;
	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		nb = va_arg(data->ap_svg, unsigned long);
	}
	else
		nb = va_arg(ap, unsigned long);
	nb = unsigned_cast(nb, form->length);
	fwp_oct(nb, form, data);
	data->field = 0;
	return (0);
}

int		print_hex(va_list ap, t_form *form, t_data *data)
{
	unsigned long	nb;

	form->pre = form->preflag ? -1 : form->pre;
	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		nb = va_arg(data->ap_svg, unsigned long);
	}
	else
		nb = va_arg(ap, unsigned long);
	nb = unsigned_cast(nb, form->length);
	fwp_hex(nb, form, data);
	data->field = 0;
	return (0);
}
