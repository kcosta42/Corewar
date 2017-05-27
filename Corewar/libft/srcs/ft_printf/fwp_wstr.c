/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwp_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:52:24 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define NUL	"(null)"

static int	wcount(wchar_t *w, int pre, t_form *form)
{
	int		len;
	int		svg;
	int		count;

	count = 0;
	while (*w && pre > 0)
	{
		if (*w <= 0x7F)
			len = 1;
		else if (*w <= 0x7FF)
			len = 2;
		else if (*w <= 0xFFFF)
			len = 3;
		else if (*w <= 0x1FFFFF)
			len = 4;
		w++;
		svg = pre;
		count += len;
		pre -= form->pre >= 0 ? len : 0;
	}
	if (form->pre != -1 && *w)
		len = form->pre - (pre == 0 ? 0 : svg);
	else
		len = count;
	return (len);
}

static int	buff_nul(t_data *data, int pos, int wlen)
{
	int i;

	i = 0;
	while (wlen-- > 0)
		addchar(data, NUL[i++], data->length + pos++);
	return (i);
}

static int	buff_w(t_data *data, wchar_t *w, int wlen, int i)
{
	wchar_t	wc;

	wc = unicode(*w, data);
	if (data->error)
		return (1);
	if (!(data->buff > wlen))
		addwc(data, wc, data->length + i, data->buff);
	return (0);
}

static int	print_ws(wchar_t *w, t_data *data, int wlen, int i)
{
	while (w && wlen > 0)
	{
		if (buff_w(data, w, wlen, i))
			return (1);
		i += data->buff;
		wlen -= data->buff;
		w++;
	}
	return (i);
}

int			fwp_wstr(wchar_t *w, t_form *form, t_data *data)
{
	int		wlen;
	int		len;
	int		i;
	int		pos;

	pos = 0;
	if (w)
		wlen = wcount(w, form->pre != -1 ? form->pre : 1, form);
	else
		wlen = (form->pre > 6 || form->pre == -1) ?
			6 : form->pre;
	len = form->width > wlen ? form->width : wlen;
	i = form->minus ? 0 : len - wlen;
	while (pos < i && !form->minus)
		addchar(data, (form->zero && !form->minus) ?
				'0' : ' ', data->length + pos++);
	if (!w)
		i += buff_nul(data, i, wlen);
	i = print_ws(w, data, wlen, i);
	while (i < len)
		addchar(data, ' ', data->length + i++);
	data->length += len;
	return (0);
}
