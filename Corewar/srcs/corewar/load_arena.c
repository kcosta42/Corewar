/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:15:13 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/27 15:01:01 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_process(t_vm *v, t_list *process, unsigned int son_pc)
{
	t_process	son;
	int			k;

	++v->nprocess;
	++v->nprocess_alive;
	ft_lstadd(&(v->process_lst), ft_lstnew(&son, sizeof(t_process)));
	((t_process *)v->process_lst->content)->carry = CARRY;
	((t_process *)v->process_lst->content)->live_since = LIVE_SINCE + 1;
	((t_process *)v->process_lst->content)->nprocess = v->nprocess;
	((t_process *)v->process_lst->content)->pc = son_pc;
	((t_process *)v->process_lst->content)->live_count = LIVE;
	((t_process *)v->process_lst->content)->op_cast = 0;
	((t_process *)v->process_lst->content)->next_op = -1;
	k = REG_NUMBER;
	while (k--)
		((t_process *)v->process_lst->content)->reg[k] = REG[k];
}

void	load_processes(t_vm *v)
{
	t_process	p;
	int			i;

	i = 0;
	while (i < v->nplayer)
	{
		++v->nprocess;
		++v->nprocess_alive;
		ft_lstadd(&(v->process_lst), ft_lstnew(&p, sizeof(t_process)));
		((t_process *)v->process_lst->content)->carry = 0;
		((t_process *)v->process_lst->content)->nprocess = v->nprocess;
		((t_process *)v->process_lst->content)->pc = v->p[i].pc_address;
		((t_process *)v->process_lst->content)->next_op = -1;
		((t_process *)v->process_lst->content)->op_cast = 0;
		((t_process *)v->process_lst->content)->live_count = 0;
		((t_process *)v->process_lst->content)->live_since = 0;
		ft_memset(&(((t_process *)v->process_lst->content)->reg), 0,
			(REG_NUMBER) * sizeof(int));
		((t_process *)v->process_lst->content)->reg[0] = v->p[i].nplayer;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1, v->p[i].prog_len, v->p[i].name, v->p[i].comment);
		i++;
	}
}

void	load_champions(t_vm *v)
{
	int space;
	int i;
	int n;

	space = MEM_SIZE / v->nplayer;
	i = 0;
	n = 0;
	ft_printf("Introducing contestants...\n");
	while (n < v->nplayer)
	{
		ft_memcpy(&(v->a.arena[i]), v->p[n].code, v->p[n].prog_len);
		ft_memset(&(v->a.owner[i]), n, v->p[n].prog_len);
		v->p[n].pc_address = i;
		i += space;
		n++;
	}
	v->last_live_id = v->nplayer - 1;
}

void	load_arena(t_vm *v)
{
	load_champions(v);
	load_processes(v);
}
