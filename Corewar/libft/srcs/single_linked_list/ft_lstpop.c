/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 14:28:45 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 14:29:23 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_lstpop(t_list **alst)
{
	void	*data;
	t_list	*tmp;

	if (!*alst)
		return (NULL);
	data = (*alst)->content;
	tmp = *alst;
	*alst = (*alst)->next;
	free(tmp);
	return (data);
}
