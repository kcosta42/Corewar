/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:28 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/20 14:28:00 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LABEL_H
# define LABEL_H

# include "lexer.h"

typedef struct		s_label
{
	int				index;
	t_list			*label;
}					t_label;

t_label				*getlabels(void);
t_label				*getlabels_use(void);

int					label_index(char *name);
int					label_value(char *name, int index);
int					add_label(char *name, int value);

int					skip_header(int input, t_token *token);
int					peek_opcode(int input, int *value, t_token *token, int op);

int					init_label(int input, int *value);

#endif
