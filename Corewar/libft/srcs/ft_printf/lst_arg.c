/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 12:30:02 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 12:48:09 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dolls(t_form *form, char **str)
{
	form->dolls = form->width;
	form->width = 0;
	(*str)++;
}

void	lst_arg(t_data *data, int i)
{
	va_copy(data->ap_svg, data->ap_cpy);
	while (--i)
		va_arg(data->ap_svg, int);
}
