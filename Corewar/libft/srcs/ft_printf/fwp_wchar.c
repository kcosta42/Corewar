/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_wchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:47:22 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	unicode(wchar_t wc, t_data *data)
{
	wchar_t c;

	data->buff = 0;
	c = 0;
	if ((0xD800 <= wc && wc <= 0xDFFF) || wc > 0x10FFFF || wc < 0x0)
		data->error = 1;
	else if (!wc)
		c = wc;
	else if (++data->buff && wc <= 0x7F)
		c = wc;
	else if (data->buff++ && wc <= 0x7FF)
		c = (0x80 + (wc & 0x3F)) * 0x100 + (wc >> 6 | 0xC0);
	else if (data->buff++ && wc <= 0xFFFF)
		c = ((0x80 + (wc & 0x3F)) * 0x100 + (0x80 + (wc >> 6 & 0x3F))) *
			0x100 + (wc >> 12 | 0xE0);
	else if (data->buff++ && wc <= 0x10FFFF)
		c = (((0x80 + (wc & 0x3F)) * 0x100 + (0x80 + (wc >> 6 & 0x3F))) *
			0x100 + (0x80 + (wc >> 12 & 0x3F))) * 0x100 + (wc >> 18 | 0xF0);
	return (c);
}

int		fwp_wchar(wchar_t wc, t_form *form, t_data *data)
{
	wchar_t	c;
	int		i;
	int		len;
	int		pos;

	pos = 0;
	c = unicode(wc, data);
	if (data->error)
		return (1);
	form->width -= wc ? 0 : 1;
	len = form->width > data->buff ? form->width : data->buff;
	i = form->minus ? 0 : len - data->buff;
	len += wc ? 0 : 1;
	while (pos < i && !form->minus)
		addchar(data, (form->zero && !form->minus) ?
				'0' : ' ', data->length + pos++);
	if (wc)
		addwc(data, c, data->length + pos, data->buff);
	else
		addchar(data, c, data->length + pos++);
	while ((pos + data->buff) < len)
		addchar(data, ' ', data->length + data->buff + pos++);
	data->length += len;
	return (0);
}
