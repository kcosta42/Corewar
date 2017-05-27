/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 16:22:07 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/22 16:32:38 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	rev_manage_reg(int input, int output, unsigned int res)
{
	char			*str;

	read(input, &res, 1);
	write(output, "r", 1);
	str = ft_itoa(res);
	write(output, str, ft_strlen(str));
	ft_strdel(&str);
	return (0);
}

static int	rev_manage_dir(int in, int out, unsigned int op, unsigned int res)
{
	char			*str;

	if (g_op_tab[op].label)
		res = fixed_read_16(in);
	else
		res = fixed_read_32(in);
	write(out, "%", 1);
	str = ft_itoa(res);
	write(out, str, ft_strlen(str));
	ft_strdel(&str);
	return (0);
}

static int	rev_manage_ind(int input, int output, unsigned int res)
{
	char			*str;

	res = fixed_read_16(input);
	str = ft_itoa(res);
	write(output, str, ft_strlen(str));
	ft_strdel(&str);
	return (0);
}

int			rev_parser_manage_octal(int input, int output, unsigned int opcode)
{
	unsigned char	args;
	int				nb;
	unsigned int	res;

	nb = -1;
	read(input, &args, 1);
	write(output, g_op_tab[opcode].name, ft_strlen(g_op_tab[opcode].name));
	write(output, " ", 1);
	while (++nb < g_op_tab[opcode].nb_arg)
	{
		res = (args >> (6 - 2 * nb)) & 0b11;
		if (res == IND_CODE)
			rev_manage_ind(input, output, res);
		else if (res == DIR_CODE)
			rev_manage_dir(input, output, opcode, res);
		else
			rev_manage_reg(input, output, res);
		if (nb < g_op_tab[opcode].nb_arg - 1)
			write(output, ", ", 1);
	}
	return (0);
}

int			rev_parser_manage_other(int input, int output, unsigned int opcode)
{
	int				nb;
	unsigned int	res;

	nb = -1;
	res = 0;
	write(output, g_op_tab[opcode].name, ft_strlen(g_op_tab[opcode].name));
	write(output, " ", 1);
	while (++nb < g_op_tab[opcode].nb_arg)
	{
		if (g_op_tab[opcode].args[nb] == IND_CODE)
			rev_manage_ind(input, output, res);
		else if (g_op_tab[opcode].args[nb] == DIR_CODE)
			rev_manage_dir(input, output, opcode, res);
		else
			rev_manage_reg(input, output, res);
		if (nb < g_op_tab[opcode].nb_arg - 1)
			write(output, ", ", 1);
	}
	return (0);
}
