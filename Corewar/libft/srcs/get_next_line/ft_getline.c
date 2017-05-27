/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:40:04 by bduron            #+#    #+#             */
/*   Updated: 2017/02/27 16:40:58 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getline(const int fd, char **line)
{
	char	buff[2];
	char	*tmp;
	int		ret;

	*line = ft_strnew(0);
	while ((ret = read(fd, buff, 1)) > 0)
	{
		buff[1] = '\0';
		if (*buff == '\n')
			break ;
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		ft_strdel(&tmp);
	}
	return (ret);
}
