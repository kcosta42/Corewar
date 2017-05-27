/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:16:09 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 13:01:02 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_ptr(va_list ap, t_form *form, t_data *data)
{
	char	*str;

	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		str = va_arg(data->ap_svg, char*);
	}
	else
		str = va_arg(ap, char*);
	fwp_ptr((unsigned long)str, form, data);
	data->field = 0;
	return (0);
}

int		get_len(va_list ap, t_form *form, t_data *data)
{
	int	*nb;

	if (form->dolls)
	{
		lst_arg(data, form->dolls);
		nb = va_arg(data->ap_svg, int*);
	}
	else
		nb = va_arg(ap, int*);
	*nb = data->length;
	data->field = 0;
	return (0);
}

int		print_str(va_list ap, t_form *form, t_data *data)
{
	char	*str;
	wchar_t *w;

	form->pre = form->preflag ? -1 : form->pre;
	if (data->field == 'S' || form->length == L)
	{
		if (form->dolls)
			lst_arg(data, form->dolls);
		w = form->dolls ? va_arg(data->ap_svg, wchar_t*)
						: va_arg(ap, wchar_t*);
		data->buff = 0;
		if (fwp_wstr(w, form, data))
			return (1);
		data->field = 0;
	}
	else
	{
		if (form->dolls)
			lst_arg(data, form->dolls);
		str = form->dolls ? va_arg(data->ap_svg, char*)
						: va_arg(ap, char*);
		fwp_str(str, form, data);
		data->field = 0;
	}
	return (0);
}

int		print_char(va_list ap, t_form *form, t_data *data)
{
	int				c;
	wchar_t			w;

	if (data->field == 'C' || form->length == L)
	{
		if (form->dolls)
			lst_arg(data, form->dolls);
		w = form->dolls ? va_arg(data->ap_svg, wchar_t)
						: va_arg(ap, wchar_t);
		data->buff = 0;
		if (fwp_wchar(w, form, data))
			return (1);
		data->field = 0;
	}
	else
	{
		if (form->dolls)
			lst_arg(data, form->dolls);
		c = form->dolls ? va_arg(data->ap_svg, int)
						: va_arg(ap, int);
		fwp_char(c, form, data);
		data->field = 0;
	}
	return (0);
}
