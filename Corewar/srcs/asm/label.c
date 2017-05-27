/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 19:43:11 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 13:10:10 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_arg	peek_arg_indirect(int input, t_token *token, t_arg arg)
{
	int			sign;

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
		arg = (t_arg){T_IND, 0, IND_SIZE};
		ft_lstaddback(&(getlabels_use()->label),
					ft_lstnew(token->str, ft_strlen(token->str) + 1));
	}
	return (arg);
}

static t_arg	peek_arg_direct(int input, t_token *token, int code, t_arg arg)
{
	int			sign;

	*token = lexer(input);
	if (token->type == (t_types){Symbol})
	{
		if (*(token->str) == '+' || *(token->str) == '-')
		{
			sign = (*(token->str) == '+') ? 1 : -1;
			*token = lexer(input);
			if (token->type == (t_types){Number})
				arg = (t_arg){T_DIR, sign * ft_atoi(token->str),
				(g_op_tab[code].label) ? DIR_SIZE / 2 : DIR_SIZE};
		}
		else if (*(token->str) == LABEL_CHAR)
		{
			*token = lexer(input);
			arg = (t_arg){T_DIR, 0, OP(code).label ? DIR_SIZE / 2 : DIR_SIZE};
			ft_lstaddback(&(getlabels_use()->label),
						ft_lstnew(token->str, ft_strlen(token->str) + 1));
		}
	}
	else if (token->type == (t_types){Number})
		arg = (t_arg){T_DIR, ft_atoi(token->str),
		(g_op_tab[code].label) ? DIR_SIZE / 2 : DIR_SIZE};
	return (arg);
}

static t_arg	peek_arg(int input, t_token *token, int opcode)
{
	t_arg			arg;

	arg = (t_arg){-1, -1, -1};
	while (token->type == (t_types){Whitespace})
		*token = lexer(input);
	if (token->type == (t_types){Symbol})
	{
		if (*(token->str) == DIRECT_CHAR)
			arg = peek_arg_direct(input, token, opcode, arg);
		else
			arg = peek_arg_indirect(input, token, arg);
	}
	else if (token->type == (t_types){Number})
		arg = (t_arg){T_IND, ft_atoi(token->str), IND_SIZE};
	else if (token->type == (t_types){Register})
		arg = (t_arg){T_REG, ft_atoi(token->str + 1), 1};
	while ((*token = lexer(input)).type == (t_types){Whitespace})
		;
	return (arg);
}

int				peek_opcode(int input, int *value, t_token *token, int opcode)
{
	int				i;
	int				j;
	t_arg			arg[3];

	i = -1;
	j = -1;
	*token = lexer(input);
	*value += 1;
	while (++i < g_op_tab[opcode].nb_arg)
	{
		if (i && token->type == (t_types){Symbol}
		&& *(token->str) == SEPARATOR_CHAR)
			*token = lexer(input);
		else if (i)
			return (2);
		if ((arg[i] = peek_arg(input, token, opcode)).size == -1)
			return (1);
		if (!(g_op_tab[opcode].args[i] & arg[i].type))
			return (3);
	}
	if (g_op_tab[opcode].octal)
		*value += 1;
	while (++j < i)
		*value += arg[j].size;
	return (0);
}

int				skip_header(int input, t_token *token)
{
	unsigned int		i;

	i = 0;
	while (i < 2)
	{
		*token = lexer(input);
		while (token->type == (t_types){Whitespace}
		|| token->type == (t_types){Newline})
			*token = lexer(input);
		if (token->type != (t_types){Symbol} || *(token->str) != '.')
			return (1);
		*token = lexer(input);
		if (token->type != (t_types){Label}
		|| ft_strcmp(token->str, (i == 0) ? "name" : "comment"))
			return (2);
		while ((*token = lexer(input)).type == (t_types){Whitespace})
			;
		if (token->type != (t_types){String})
			return (3);
		while ((*token = lexer(input)).type != (t_types){Newline})
			if (token->type != (t_types){Whitespace})
				return (4);
		i++;
	}
	return (0);
}
