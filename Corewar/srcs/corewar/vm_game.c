/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:18:18 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/23 20:52:40 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	kill_processes_lst(t_vm *v)
{
	t_list *process;
	t_list *previous;

	process = v->process_lst;
	previous = NULL;
	while (process)
	{
		if (!LIVE || v->cycle_to_die < 0)
		{
			if (process == v->process_lst)
				process = kill_head_lst(v, process);
			else
				process = kill_elem_lst(v, process, &previous);
			--v->nprocess_alive;
		}
		else
		{
			LIVE = 0;
			previous = process;
			process = process->next;
		}
	}
}

void	browse_processes_lst(t_vm *v)
{
	t_list *process;

	process = v->process_lst;
	while (process)
	{
		if (!(NEXT_OP >= 0 && NEXT_OP <= 15))
			init_next_op(v, process);
		if (OP_CAST == 0)
		{
			if (NEXT_OP >= 0 && NEXT_OP < 16)
			{
				g_op_tab[NEXT_OP].f(v, process);
				NEXT_OP = -1;
			}
		}
		else
			OP_CAST -= 1;
		LIVE_SINCE++;
		process = process->next;
	}
}

void	update_vm(t_vm *v)
{
	if (BCTD)
	{
		v->is_ctd_modified = 0;
		if (v->nlive_bctd >= NBR_LIVE)
		{
			v->cycle_to_die -= CYCLE_DELTA;
			v->is_ctd_modified = 1;
			if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_CYCLES))
				ft_printf("Cycle to die is now %d\n", v->cycle_to_die);
		}
		v->ncheck = v->is_ctd_modified ? 0 : v->ncheck + 1;
		if (v->ncheck % MAX_CHECKS == 0)
		{
			if (!v->is_ctd_modified && v->ncheck != 0)
			{
				v->cycle_to_die -= CYCLE_DELTA;
				if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_CYCLES))
					ft_printf("Cycle to die is now %d\n", v->cycle_to_die);
			}
		}
		v->nlive_bctd = 0;
		v->ncycle_mod = 0;
	}
	v->ncycle++;
	v->ncycle_mod++;
}

void	run_game(t_vm *v)
{
	while (v->process_lst != NULL)
	{
		if (v->ncycle == v->dump_param)
		{
			print_arena(v);
			break ;
		}
		update_vm(v);
		if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_CYCLES))
			ft_printf("It is now cycle %d\n", v->ncycle);
		if (v->process_lst)
		{
			browse_processes_lst(v);
			if ((BCTD) || v->cycle_to_die < 0)
				kill_processes_lst(v);
		}
	}
	if (v->ncycle != v->dump_param)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		v->last_live_id + 1, v->p[v->last_live_id].name);
}
