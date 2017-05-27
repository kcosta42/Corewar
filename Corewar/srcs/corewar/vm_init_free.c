/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:37:52 by bduron            #+#    #+#             */
/*   Updated: 2017/04/23 20:39:20 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_list	*kill_head_lst(t_vm *v, t_list *process)
{
	v->process_lst = process->next;
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_DEATH))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				NPRO, LIVE_SINCE, v->cycle_to_die);
	free(process->content);
	free(process);
	process = v->process_lst;
	return (process);
}

t_list	*kill_elem_lst(t_vm *v, t_list *process, t_list **previous)
{
	if (DISPLAY && process && (v->verbose_param & FLAG_VERBOSE_DEATH))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				NPRO, LIVE_SINCE, v->cycle_to_die);
	process = process->next;
	free((*previous)->next->content);
	free((*previous)->next);
	(*previous)->next = process;
	return (process);
}

void	vm_init_var(t_vm *v)
{
	v->process_lst = NULL;
	v->nprocess = 0;
	v->nprocess_alive = 0;
	v->ncycle = 0;
	v->ncycle_mod = 0;
	v->ncheck = 0;
	v->nlive_bctd = 0;
	v->cycle_to_die = CYCLE_TO_DIE;
	v->is_ctd_modified = 0;
	v->opt_flags = 0;
	v->dump_param = -1;
	v->verbose_param = 0;
	v->nplayer = 0;
	v->nplayer_cust = 0;
}

void	vm_init(t_vm *v)
{
	int i;

	ft_memset(v->a.arena, 0, sizeof(unsigned char) * MEM_SIZE);
	ft_memset(v->a.owner, -1, sizeof(char) * MEM_SIZE);
	ft_memset(v->a.type, -1, sizeof(char) * MEM_SIZE);
	vm_init_var(v);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->p[i].nplayer = 0;
		ft_memset(v->p[i].name, 0, PROG_NAME_LENGTH);
		ft_memset(v->p[i].comment, 0, COMMENT_LENGTH);
		ft_memset(v->p[i].code, 0, CHAMP_MAX_SIZE);
		i++;
	}
}
