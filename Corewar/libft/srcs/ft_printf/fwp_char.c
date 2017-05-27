/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fwp_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:25:37 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 11:29:59 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define NUL	"(null)"

static void	fill_str(t_data *data, char *str, int wlen, int pos)
{
	int	i;

	i = 0;
	if (str)
		while (wlen--)
			addchar(data, str[i++], data->length + pos++);
	else
		while (wlen--)
			addchar(data, NUL[i++], data->length + pos++);
}

void		fwp_str(char *str, t_form *form, t_data *data)
{
	int		len;
	int		wlen;
	char	fill;
	int		pos;

	pos = 0;
	wlen = str ? ft_strlen(str) : 6;
	wlen = (form->pre < wlen && form->pre != -1) ? form->pre : wlen;
	len = form->width > wlen ? form->width : wlen;
	fill = (!form->minus && form->zero) ? '0' : ' ';
	while (pos < len - wlen && !form->minus)
		addchar(data, fill, data->length + pos++);
	fill_str(data, str, wlen, pos);
	pos += wlen;
	while (pos < len && form->minus)
		addchar(data, fill, data->length + pos++);
	data->length += len;
}

void		fwp_char(int c, t_form *form, t_data *data)
{
	int		len;
	char	fill;
	int		pos;

	len = form->width > 0 ? form->width : 1;
	fill = (!form->minus && form->zero) ? '0' : ' ';
	pos = form->minus ? data->length : data->length + len - 1;
	len += pos;
	while (data->length < pos)
		addchar(data, fill, data->length++);
	addchar(data, c, data->length++);
	while (data->length < len && form->minus)
		addchar(data, fill, data->length++);
}
