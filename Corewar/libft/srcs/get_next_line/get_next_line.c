/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:59:02 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:27:58 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *tmp_free;

	tmp_free = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp_free);
	return (s1);
}

int		flush_tmp(char **tmp, char *bufchr, char **line)
{
	if (*tmp && (bufchr = ft_strchr(*tmp, '\n')))
	{
		*bufchr = '\0';
		*line = ft_strdup(*tmp);
		*tmp = ft_strdup(bufchr + 1);
		return (1);
	}
	else
		return (0);
}

int		no_newline(char **tmp, char *bufchr, char **line)
{
	if (*tmp && !bufchr && **tmp)
	{
		*line = *tmp;
		*tmp = NULL;
		return (1);
	}
	else
		return (0);
}

int		next_newline(char **tmp, char **bufchr, char *buf, char **line)
{
	if ((*bufchr = ft_strchr((const char *)buf, '\n')))
	{
		**bufchr = '\0';
		*line = !*tmp ? ft_strdup(buf) : ft_strjoin_free(*tmp, buf);
		*tmp = ft_strdup(*bufchr + 1);
		return (1);
	}
	else
		return (0);
}

int		get_next_line(int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*tmp;
	char		*bufchr;
	int			n;

	bufchr = NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (flush_tmp(&tmp, bufchr, line))
		return (1);
	ft_memset(buf, '\0', BUFF_SIZE + 1);
	while ((n = read(fd, buf, BUFF_SIZE)))
	{
		if (n == -1)
			return (n);
		if (next_newline(&tmp, &bufchr, buf, line))
			return (1);
		else
			tmp = !tmp ? ft_strdup(buf) : ft_strjoin_free(tmp, buf);
		ft_memset(buf, '\0', BUFF_SIZE + 1);
	}
	if (no_newline(&tmp, bufchr, line))
		return (1);
	return (n == 0) ? 0 : -1;
}
