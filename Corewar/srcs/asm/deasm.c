/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 16:04:32 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/22 16:22:28 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	rev_parse_header(int input, int output)
{
	char	c;
	int		index;
	int		i;
	char	*type;
	int		limit;

	i = -1;
	while (++i < 2)
	{
		index = 0;
		type = (i) ? ".comment \"" : ".name \"";
		limit = (i) ? COMMENT_LENGTH + 4 : PROG_NAME_LENGTH + 4;
		read(input, (char[4]){0}, 4);
		read(input, &c, 1);
		write(output, type, ft_strlen(type));
		while (++index < limit && c)
		{
			write(output, &c, 1);
			read(input, &c, 1);
		}
		write(output, "\"\n", ft_strlen("\"\n"));
		while (index++ < limit)
			read(input, &c, 1);
	}
	return (0);
}

static int	rev_parser(int input, int output)
{
	unsigned int	opcode;
	unsigned char	code;

	write(output, "\n", 1);
	while (read(input, &code, 1) > 0)
	{
		opcode = code - 1;
		if (opcode > 16)
			return (1);
		if (g_op_tab[opcode].octal)
			rev_parser_manage_octal(input, output, opcode);
		else
			rev_parser_manage_other(input, output, opcode);
		write(output, "\n", 1);
	}
	return (0);
}

int			ft_decompile(char *input_name, char *output_name)
{
	int		input;
	int		output;

	if ((input = open(input_name, O_RDONLY)) < 0)
		return (ft_error("Can't read source file", 1));
	if ((output = open(output_name, O_CREAT | O_RDWR, 0644)) < 0)
		return (2);
	rev_parse_header(input, output);
	if (rev_parser(input, output))
		return (ft_error("Failed to finish disassembling.", 3));
	return (0);
}
