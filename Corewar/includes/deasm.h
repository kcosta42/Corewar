/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 16:04:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/22 16:31:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEASM_H
# define DEASM_H

# include "libft.h"

int		ft_decompile(char *input_name, char *output_name);
int		rev_parser_manage_octal(int input, int output, unsigned int opcode);
int		rev_parser_manage_other(int input, int output, unsigned int opcode);

#endif
