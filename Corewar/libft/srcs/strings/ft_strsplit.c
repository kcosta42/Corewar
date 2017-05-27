/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:36:33 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:11 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strlen_del(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static int		ft_wordcount(char *s, char c)
{
	int		wc;
	char	lc;

	lc = c;
	wc = 0;
	while (*s)
	{
		if (*s != lc && lc == c)
			wc++;
		lc = *s;
		s++;
	}
	return (wc);
}

static void		ft_fill(char **split, char *s, char c, char lc)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (*s)
	{
		len = 0;
		if (lc == c && *s != c)
		{
			len = ft_strlen_del(s, c);
			j = 0;
			if (!(split[i] = (char *)malloc(sizeof(char) * (len + 1))))
				return ;
			while (*s != c && *s)
				split[i][j++] = *s++;
			split[i++][j] = '\0';
			lc = *s;
		}
		else
			lc = *s++;
	}
	split[i] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		wc;

	if (!s || !c)
		return (NULL);
	wc = ft_wordcount((char *)s, c);
	if (!(split = (char **)malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	ft_fill(split, (char *)s, c, c);
	return (split);
}
