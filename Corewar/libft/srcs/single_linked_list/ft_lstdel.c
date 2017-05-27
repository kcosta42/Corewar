/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 17:30:06 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:36:01 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (!*alst || !del)
		return ;
	tmp = *alst;
	while (tmp)
	{
		*alst = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = *alst;
	}
	*alst = NULL;
}
