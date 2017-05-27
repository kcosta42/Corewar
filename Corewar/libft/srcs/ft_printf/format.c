/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:02 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 12:38:33 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		field(t_data *data, char **str)
{
	if (**str == 's' || **str == 'S' || **str == 'p' || **str == 'd' ||
		**str == 'D' || **str == 'i' || **str == 'o' || **str == 'O' ||
		**str == 'u' || **str == 'U' || **str == 'x' || **str == 'X' ||
		**str == 'c' || **str == 'C' || **str == 'b' || **str == 'B' ||
		**str == 'n')
		data->field = *(*str)++;
	else
		data->field = 0;
	return (0);
}

int		length(char **str, t_form *form)
{
	if (**str != 'j' && **str != 'h' && **str != 'l' && **str != 'z')
		return (0);
	form->length = (**str == 'h' && form->length < H) ? H : form->length;
	form->length = !ft_strncmp(*str, "hh", 2) ? HH : form->length;
	form->length = !ft_strncmp(*str, "l", 1) ? L : form->length;
	form->length = !ft_strncmp(*str, "ll", 2) ? LL : form->length;
	form->length = !ft_strncmp(*str, "z", 1) ? Z : form->length;
	form->length = !ft_strncmp(*str, "j", 1) ? J : form->length;
	if (form->length != -1)
		*str += form->length > 3 ? 2 : 1;
	return (0);
}

int		precision(va_list ap, char **str, t_form *form)
{
	int nb;

	if (**str == '.')
	{
		form->pre = 0;
		(*str)++;
		if (ft_isdigit(**str))
			while (ft_isdigit(**str))
				form->pre = 10 * form->pre + *(*str)++ - '0';
		else if (**str == '*')
		{
			nb = va_arg(ap, int);
			form->pre = nb >= 0 ? nb : 0;
			form->preflag = nb >= 0 ? 0 : 1;
			(*str)++;
		}
		else
			form->pre = 0;
	}
	return (0);
}

int		width(va_list ap, char **str, t_form *form)
{
	int nb;

	if (ft_isdigit(**str))
		form->width = 0;
	while (ft_isdigit(**str))
		form->width = 10 * form->width + *(*str)++ - '0';
	if (**str == '*')
	{
		nb = va_arg(ap, int);
		form->width = nb >= 0 ? nb : nb * -1;
		form->minus = nb < 0 ? 1 : form->minus;
		(*str)++;
	}
	else if (**str == '$')
		dolls(form, str);
	return (0);
}

int		flags(char **str, t_form *form)
{
	while (**str == '-' || **str == '+' || **str == ' ' ||
			**str == '0' || **str == '#' || **str == 39)
	{
		form->minus = **str == '-' ? 1 : form->minus;
		form->plus = **str == '+' ? 1 : form->plus;
		form->space = **str == ' ' ? 1 : form->space;
		form->zero = **str == '0' ? 1 : form->zero;
		form->hash = **str == '#' ? 1 : form->hash;
		form->apo = **str == 39 ? 1 : form->apo;
		(*str)++;
	}
	return (0);
}
