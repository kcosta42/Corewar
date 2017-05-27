/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:28 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 17:12:21 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct		s_arg
{
	char			type;
	int				value;
	int				size;
}					t_arg;

int					parse_header(int in, int out, t_token *token, int *value);
int					parse_opcode(int in, int out, t_token *token, int opcode);

int					ft_compile(char *input_name, char *output_name);

#endif
