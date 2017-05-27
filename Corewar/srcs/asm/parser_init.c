/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:04:17 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/20 14:20:23 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		parser_skip_white(int input, t_token *token)
{
	while (token->type == (t_types){Whitespace}
	|| token->type == (t_types){Newline})
		*token = lexer(input);
	return (0);
}

static int		parser_manage_label(int input, t_token *token)
{
	if ((*token = lexer(input)).type != (t_types){Symbol}
	|| *(token->str) != LABEL_CHAR)
		return (5);
	*token = lexer(input);
	return (0);
}

static int		parser_manage_keyword(int input, int output, t_token *token)
{
	if (parse_opcode(input, output, token, ft_getkeyword(token->str)))
		return (6);
	while (token->type != (t_types){Newline})
	{
		if (token->type != (t_types){Whitespace})
			return (7);
		*token = lexer(input);
	}
	return (0);
}

static int		ft_parser(int input, int output, t_token *token)
{
	parser_skip_white(input, token);
	if (token->type == (t_types){Label})
		parser_manage_label(input, token);
	else if (token->type == (t_types){Keyword})
		parser_manage_keyword(input, output, token);
	else if (token->type != (t_types){None})
		return (12);
	return (0);
}

int				ft_compile(char *input_name, char *output_name)
{
	t_token			token;
	int				input;
	int				output;
	int				value;

	if ((input = open(input_name, O_RDONLY)) < 0)
		return (ft_error("Can't read source file", 1));
	if (init_label(input, &value))
		return (-1);
	if ((output = open(output_name, O_CREAT | O_RDWR, 0644)) < 0)
		return (3);
	if (parse_header(input, output, &token, &value))
		return (4);
	while (token.type != (t_types){None})
		if (ft_parser(input, output, &token))
			return (1);
	return (0);
}
