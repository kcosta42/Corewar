/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinttab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:27:58 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 14:30:04 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*ft_lstinttab(t_list *alst)
{
	int		*tab;
	int		len;
	int		i;

	if (!alst)
		return (NULL);
	len = ft_lstlen(alst);
	tab = malloc(sizeof(int) * len);
	i = 0;
	while (i < len)
	{
		tab[i++] = *(int *)(alst->content);
		alst = alst->next;
	}
	return (tab);
}
