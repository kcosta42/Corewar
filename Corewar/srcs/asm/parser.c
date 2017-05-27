/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:22 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/19 12:50:32 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_arg	parse_arg_indirect(int input, t_token *token, t_arg arg)
{
	int		sign;

	if (*(token->str) == '+' || *(token->str) == '-')
	{
		sign = (*(token->str) == '+') ? 1 : -1;
		*token = lexer(input);
		if (token->type == (t_types){Number})
			arg = (t_arg){T_IND, sign * ft_atoi(token->str), IND_SIZE};
	}
	else if (*(token->str) == LABEL_CHAR)
	{
		*token = lexer(input);
		if (label_index(token->str) != -1)
			arg = (t_arg){T_IND, label_value(token->str,
						getlabels()->index), IND_SIZE};
	}
	return (arg);
}

static t_arg	parse_arg_direct(int in, t_token *token, int opcode, t_arg arg)
{
	int		sign;

	*token = lexer(in);
	if (token->type == (t_types){Symbol})
	{
		if (*(token->str) == '+' || *(token->str) == '-')
		{
			sign = (*(token->str) == '+') ? 1 : -1;
			*token = lexer(in);
			if (token->type == (t_types){Number})
				arg = (t_arg){T_DIR, sign * ft_atoi(token->str),
				(g_op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
		}
		else if (*(token->str) == LABEL_CHAR)
		{
			*token = lexer(in);
			if (label_index(token->str) != -1)
				arg = (t_arg){T_DIR, label_value(token->str,
		getlabels()->index), g_op_tab[opcode].label ? DIR_SIZE / 2 : DIR_SIZE};
		}
	}
	else if (token->type == (t_types){Number})
		arg = (t_arg){T_DIR, ft_atoi(token->str),
		(g_op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
	return (arg);
}

static t_arg	parse_arg(int input, t_token *token, int opcode)
{
	t_arg			arg;

	arg = (t_arg){-1, -1, -1};
	while (token->type == (t_types){Whitespace})
		*token = lexer(input);
	if (token->type == (t_types){Symbol})
	{
		if (*(token->str) == DIRECT_CHAR)
			arg = parse_arg_direct(input, token, opcode, arg);
		else
			arg = parse_arg_indirect(input, token, arg);
	}
	else if (token->type == (t_types){Number})
		arg = (t_arg){T_IND, ft_atoi(token->str), IND_SIZE};
	else if (token->type == (t_types){Register})
		arg = (t_arg){T_REG, ft_atoi(token->str + 1), 1};
	while ((*token = lexer(input)).type == (t_types){Whitespace})
		;
	return (arg);
}

static int		parse_opcode_file(int par, int output, int i[2], t_arg arg[3])
{
	int			j;

	j = i[0];
	while (j++ < 4)
		par = par << 2;
	j = -1;
	if (g_op_tab[i[1]].octal)
	{
		fixed_write(output, &par, 1);
		getlabels()->index += 1;
	}
	while (++j < i[0])
	{
		fixed_write(output, &(arg[j].value), arg[j].size);
		getlabels()->index += arg[j].size;
	}
	getlabels()->index += 1;
	return (0);
}

int				parse_opcode(int input, int output, t_token *token, int opcode)
{
	int				i[2];
	int				par;
	t_arg			arg[3];

	par = 0;
	i[0] = -1;
	i[1] = opcode;
	*token = lexer(input);
	fixed_write(output, &(g_op_tab[opcode].opcode), 1);
	while (++i[0] < g_op_tab[opcode].nb_arg)
	{
		if (i[0] && token->type == (t_types){Symbol}
		&& *(token->str) == SEPARATOR_CHAR)
			*token = lexer(input);
		else if (i[0])
			return (2);
		if ((arg[i[0]] = parse_arg(input, token, opcode)).size == -1)
			return (1);
		if (!(g_op_tab[opcode].args[i[0]] & arg[i[0]].type))
			return (3);
		arg[i[0]].type = (arg[i[0]].type == T_IND) ? IND_CODE : arg[i[0]].type;
		par = (par << 2) + arg[i[0]].type;
	}
	parse_opcode_file(par, output, i, arg);
	return (0);
}
