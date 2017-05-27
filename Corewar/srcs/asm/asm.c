/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:14:44 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 13:35:37 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_clean(int ret)
{
	ft_lstdel(&(getlabels()->label), &ft_delete_label);
	ft_lstdel(&(getlabels_use()->label), &ft_delete_label);
	return (ret);
}

int				label_error(char *str, int ft_errnum)
{
	ft_putstr("No such label ");
	ft_putstr(str);
	ft_putstr(" while attempting to dereference token \":");
	ft_putstr(str);
	ft_putendl("\"");
	return (ft_errnum);
}

static char		*ft_rev_check_file(char *filename)
{
	char	*extension;
	char	*output;

	output = NULL;
	extension = ft_strrchr(filename, '.');
	if (!extension)
		return (NULL);
	if (ft_strcmp(extension, ".cor"))
		return (NULL);
	output = ft_strnew(extension - filename + 2);
	ft_strncpy(output, filename, extension - filename + 1);
	ft_strncpy(ft_strrchr(output, '.') + 1, "s", 1);
	return (output);
}

static char		*ft_check_file(char *filename)
{
	char	*extension;
	char	*output;

	output = NULL;
	extension = ft_strrchr(filename, '.');
	if (!extension)
		return (NULL);
	if (ft_strcmp(extension, ".s"))
		return (NULL);
	output = ft_strnew(extension - filename + 4);
	ft_strncpy(output, filename, extension - filename + 1);
	ft_strncpy(ft_strrchr(output, '.') + 1, "cor", 3);
	return (output);
}

int				main(int argc, char **argv)
{
	char	*output;
	int		ret;

	if (argc < 2 || argc > 3)
		return (ft_error("usage: ./asm [-d champion.cor] | champion.s", 1));
	if (!ft_strcmp(argv[1], "-d"))
	{
		if (argc != 3)
			return (ft_error("usage: ./asm [-d champion.cor] | champion.s", 1));
		if (!(output = ft_rev_check_file(argv[2])))
			return (ft_error("Can't read source file\n", 1));
		if ((ret = ft_decompile(argv[2], output)))
			return (ft_clean(ret));
	}
	else
	{
		if (!(output = ft_check_file(argv[1])))
			return (ft_error("Can't read source file\n", 1));
		if ((ret = ft_compile(argv[1], output)))
			return (ft_clean(ret));
	}
	ft_putstr("Writing output program to ");
	ft_putendl(output);
	ft_strdel(&output);
	return (ft_clean(0));
}
