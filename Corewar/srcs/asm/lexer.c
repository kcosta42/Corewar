/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:41 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/20 13:56:16 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_token			ft_tokenupdate(t_token token, t_types type, char chr)
{
	unsigned int		index;

	token.type = type;
	index = ft_strlen(token.str);
	if (index < COMMENT_LENGTH)
		token.str[ft_strlen(token.str)] = chr;
	return (token);
}

static t_char			lexer_manage_white(t_token *token, t_char chr, int fd)
{
	while (ft_strchr(WHITESPACE_CHARS, chr.c)
		|| chr.c == COMMENT_CHAR || chr.c == COMMENT_CHAR_2)
	{
		while (ft_strchr(WHITESPACE_CHARS, chr.c))
		{
			token->type = (t_types){Whitespace};
			while (ft_strchr(WHITESPACE_CHARS, chr.c))
			{
				if (chr.c == '\n')
					token->type = (t_types){Newline};
				chr = scanner(fd);
			}
		}
		while (chr.c == COMMENT_CHAR || chr.c == COMMENT_CHAR_2)
		{
			token->type = (t_types){Comment};
			while (chr.c != '\n')
			{
				if (chr.c == 0)
					return ((t_char){0, 0, 0});
				chr = scanner(fd);
			}
		}
	}
	return (chr);
}

static t_char			lexer_manage_label(t_token *token, t_char chr, int fd)
{
	*token = ft_tokenupdate(*token, (t_types){Label}, chr.c);
	chr = scanner(fd);
	while (ft_strchr(LABEL_CHARS, chr.c))
	{
		*token = ft_tokenupdate(*token, token->type, chr.c);
		chr = scanner(fd);
	}
	if (chr.c == LABEL_CHAR)
		;
	else if (ft_iskeyword(token->str))
		token->type = (t_types){Keyword};
	else if (ft_strisdigit(token->str))
		token->type = (t_types){Number};
	else if (ft_isregister(token->str))
		token->type = (t_types){Register};
	return (chr);
}

static t_char			lexer_manage_string(t_token *token, t_char chr, int fd)
{
	token->type = (t_types){String};
	chr = scanner(fd);
	while (chr.c != '"')
	{
		if (chr.c == 0)
			return ((t_char){0, 0, 0});
		*token = ft_tokenupdate(*token, token->type, chr.c);
		chr = scanner(fd);
	}
	chr = scanner(fd);
	return (chr);
}

t_token					lexer(int fd)
{
	t_token				token;
	static t_char		chr = {-1, -1, -1};

	chr = (chr.c != -1) ? chr : scanner(fd);
	token = (t_token){{0}, (chr.c != -1) ? -1 : 0, 0, 0};
	token.col = chr.col;
	token.line = chr.line;
	ft_memset(token.str, 0, COMMENT_LENGTH + 1);
	if (ft_strchr(WHITESPACE_CHARS, chr.c) ||
		chr.c == COMMENT_CHAR || chr.c == COMMENT_CHAR_2)
		chr = lexer_manage_white(&token, chr, fd);
	else if (ft_strchr(SYMBOL_CHARS, chr.c))
	{
		token = ft_tokenupdate(token, (t_types){Symbol}, chr.c);
		chr = scanner(fd);
	}
	else if (chr.c == '"')
		chr = lexer_manage_string(&token, chr, fd);
	else if (ft_strchr(LABEL_CHARS, chr.c))
		chr = lexer_manage_label(&token, chr, fd);
	return (token);
}
