/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:00:46 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/20 15:32:25 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_error(char *msg, int ft_errnum)
{
	ft_putendl_fd(msg, 2);
	return (ft_errnum);
}

int		ft_iskeyword(char *word)
{
	int					i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (!(ft_strcmp(g_op_tab[i].name, word)))
			return (1);
		i++;
	}
	return (0);
}

int		ft_getkeyword(char *word)
{
	int					i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (!(ft_strcmp(g_op_tab[i].name, word)))
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strisdigit(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int		ft_isregister(char *word)
{
	if (*word != 'r')
		return (0);
	if (!ft_strisdigit(word + 1))
		return (0);
	if (*(word + 3))
		return (0);
	return (1);
}
