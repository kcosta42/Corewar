/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:55 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 14:34:51 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define WHITESPACE_CHARS		"\t\n\v\f\r "
# define SYMBOL_CHARS			"#:%,.-+"
# define COMMENT_CHAR_2			';'

typedef enum		e_types
{
	Unknown = -1,
	None = 0,
	Comment,
	Whitespace,
	Newline,
	Label,
	Keyword,
	Register,
	Symbol,
	String,
	Number
}					t_types;

typedef struct		s_token
{
	char			str[COMMENT_LENGTH + 1];
	t_types			type;
	int				col;
	int				line;
}					t_token;

t_token				lexer(int fd);

#endif
