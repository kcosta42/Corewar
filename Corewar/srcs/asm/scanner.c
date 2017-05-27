/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:52:23 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 13:36:15 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					ft_delete_label(void *content, size_t size)
{
	ft_strdel((char**)&content);
	size = 0;
}

int						lexical_error(t_token token, int ft_errnum)
{
	ft_putstr("Lexical error at [");
	ft_putnbr(token.line);
	ft_putstr(":");
	ft_putnbr(token.col);
	ft_putendl("]");
	return (ft_errnum);
}

t_char					scanner(int fd)
{
	static int			col = 0;
	static int			line = 1;
	char				c;

	col++;
	if (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			col = 0;
			line++;
		}
		return ((t_char){c, col, line});
	}
	else
		return ((t_char){-1, col, line});
}
