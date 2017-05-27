/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:15:53 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 14:02:08 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_fct_tab.h"

static void	init_data(t_data *data)
{
	data->length = 0;
	data->index = 0;
	data->field = 0;
	data->error = 0;
	data->fd = 1;
	data->sprintf = NULL;
}

int			ft_printf(char *fmt, ...)
{
	va_list		ap;
	t_data		data;
	t_form		form;
	int			i;
	static int	err = 0;

	va_start(ap, fmt);
	va_copy(data.ap_cpy, ap);
	init_data(&data);
	while (*fmt && !data.error)
	{
		i = 0;
		parser(&data, &fmt, &form, ap);
		while (data.field && g_fct_tab[i].c && g_fct_tab[i].c != data.field)
			i++;
		if (data.field && g_fct_tab[i].f != NULL)
			if (g_fct_tab[i].f(ap, &form, &data))
				err = 1;
	}
	va_end(ap);
	if (!data.error && data.length)
		write(data.fd, data.buffer, data.length % BUFF ?
				data.length % BUFF : BUFF);
	return (err ? -1 : data.length);
}

int			ft_dprintf(int fd, char *fmt, ...)
{
	va_list		ap;
	t_data		data;
	t_form		form;
	int			i;

	va_start(ap, fmt);
	va_copy(data.ap_cpy, ap);
	init_data(&data);
	data.fd = fd;
	while (*fmt && !data.error)
	{
		i = 0;
		parser(&data, &fmt, &form, ap);
		while (data.field && g_fct_tab[i].c && g_fct_tab[i].c != data.field)
			i++;
		if (data.field && g_fct_tab[i].f != NULL)
			g_fct_tab[i].f(ap, &form, &data);
	}
	va_end(ap);
	if (!data.error && data.length)
		write(data.fd, data.buffer, data.length % BUFF ?
				data.length % BUFF : BUFF);
	return (data.length);
}

int			ft_sprintf(char *str, char *fmt, ...)
{
	va_list		ap;
	t_data		data;
	t_form		form;
	int			i;

	va_start(ap, fmt);
	va_copy(data.ap_cpy, ap);
	init_data(&data);
	data.sprintf = str;
	while (*fmt && !data.error)
	{
		i = 0;
		parser(&data, &fmt, &form, ap);
		while (data.field && g_fct_tab[i].c && g_fct_tab[i].c != data.field)
			i++;
		if (data.field && g_fct_tab[i].f != NULL)
			g_fct_tab[i].f(ap, &form, &data);
	}
	va_end(ap);
	str[data.length] = '\0';
	return (data.length);
}
/*
**int		ft_fprintf(FILE *stream, char *fmt, ...)
**{
**	va_list		ap;
**	t_data		data;
**	t_form		form;
**	int			i;
**
**	va_start(ap, fmt);
**	init_data(&data);
**	data.fd = fileno(stream);
**	while (*fmt && !data.error)
**	{
**		i = 0;
**		parser(&data, &fmt, &form, ap);
**		while (data.field && g_fct_tab[i].c && g_fct_tab[i].c != data.field)
**			i++;
**		if (data.field && g_fct_tab[i].f != NULL)
**			g_fct_tab[i].f(ap, &form, &data);
**	}
**	va_end(ap);
**	if (!data.error && data.length)
**		write(data.fd, data.buffer, data.length % BUFF ?
**				data.length % BUFF : BUFF);
**	return (data.length);
**}
*/
