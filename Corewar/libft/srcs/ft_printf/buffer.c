/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 10:20:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/01/22 13:55:49 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	addwc(t_data *data, wchar_t wc, int pos, int len)
{
	if (data->sprintf)
	{
		data->sprintf[pos++] = (wc & 0xFF);
		while (--len)
		{
			wc >>= 8;
			data->sprintf[pos++] = (wc & 0xFF);
		}
		return (0);
	}
	if (pos != 0 && pos % BUFF == 0)
		write(data->fd, data->buffer, BUFF);
	data->buffer[pos++ % BUFF] = (wc & 0xFF);
	while (--len)
	{
		if (pos != 0 && pos % BUFF == 0)
			write(data->fd, data->buffer, BUFF);
		wc >>= 8;
		data->buffer[pos++ % BUFF] = (wc & 0xFF);
	}
	return (0);
}

int	addchar(t_data *data, char c, int pos)
{
	if (data->sprintf)
	{
		data->sprintf[pos] = c;
		return (0);
	}
	if (pos != 0 && pos % BUFF == 0)
		write(data->fd, data->buffer, BUFF);
	data->buffer[pos % BUFF] = c;
	return (0);
}
