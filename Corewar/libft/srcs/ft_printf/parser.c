/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:33:43 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 12:39:06 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_format(t_form *form, t_data *data)
{
	form->minus = 0;
	form->plus = 0;
	form->space = 0;
	form->zero = 0;
	form->hash = 0;
	form->width = 0;
	form->pre = -1;
	form->preflag = 0;
	form->length = -1;
	data->field = 0;
	form->nul = 0;
	form->apo = 0;
	form->dolls = 0;
}

static int	str_parse(t_data *data, char **str)
{
	while ((**str && **str != '%') || (**str == '%' && !*(*str + 1)))
	{
		if (**str != 37)
			addchar(data, **str, data->length++);
		(*str)++;
	}
	return (0);
}

static int	isform(char c)
{
	if (ft_isdigit(c) || c == '.' || c == '+' || c == ' ' || c == '-' ||
	c == '#' || c == 'j' || c == 'h' || c == 'l' || c == 'z' || c == '*'
	|| c == 39)
		return (1);
	return (0);
}

static void	fail(t_data *data, t_form *form, char **str)
{
	int		len;
	char	c;
	int		pos;

	pos = 0;
	if (!form->width && **str)
		addchar(data, *(*str)++, data->length++);
	else if (**str)
	{
		if (isform(**str) || **str == 'L' || **str == 'q' || **str == 'I')
			(*str)++;
		len = form->width;
		c = (form->zero && !form->minus) ? 48 : 32;
		while (pos < (len - 1) && !form->minus)
			addchar(data, c, data->length + pos++);
		addchar(data, *(*str)++, data->length + pos++);
		while (pos < len && form->minus)
			addchar(data, c, data->length + pos++);
		data->length += len;
	}
}

int			parser(t_data *data, char **str, t_form *form, va_list ap)
{
	str_parse(data, str);
	if (**str && *(*str + 1))
	{
		(*str)++;
		init_format(form, data);
		while (isform(**str))
		{
			flags(str, form);
			width(ap, str, form);
			precision(ap, str, form);
			length(str, form);
		}
		field(data, str);
		if (!data->field)
			fail(data, form, str);
	}
	return (0);
}
