/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:13:08 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/22 14:06:13 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "op.h"
# include "scanner.h"
# include "lexer.h"
# include "label.h"
# include "parser.h"
# include "fixed_io.h"
# include "deasm.h"

# define OP(index)	g_op_tab[index]

int		ft_error(char *msg, int ft_errnum);
int		label_error(char *str, int ft_errnum);
int		ft_iskeyword(char *word);
int		ft_getkeyword(char *word);
int		ft_strisdigit(char *str);
int		ft_isregister(char *word);

#endif
