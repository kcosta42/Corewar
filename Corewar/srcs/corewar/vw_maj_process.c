/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_maj_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 11:38:36 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/23 20:53:15 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	maj_process_selected(t_viewer *v, t_process *selected)
{
	if (selected)
	{
		wattron(v->win_arena, COLOR_PAIR(14));
		mvwprintw(v->win_arena, selected->pc / 64, (selected->pc % 64 * 3),
			"%.2x", v->vm->a.arena[selected->pc]);
		wattroff(v->win_arena, COLOR_PAIR(14));
		maj_register(v, selected);
	}
}

static void	maj_process_arena(t_viewer *v)
{
	t_list *process;

	process = v->vm->process_lst;
	while (process)
	{
		wattron(v->win_arena, COLOR_FG(v->vm->a.owner[PC]));
		mvwprintw(v->win_arena, PC / 64, (PC % 64 * 3), "%.2x",
			v->vm->a.arena[PC]);
		wattroff(v->win_arena, COLOR_FG(v->vm->a.owner[PC]));
		process = process->next;
	}
}

static void	maj_process_print_msg(t_viewer *v, t_list *process, int i)
{
	if (NEXT_OP >= 0 && NEXT_OP < 16)
		mvwprintw(v->win_processes, i - v->process_offset, 20,
			"          will cast a \"%5s\" in %4d laps.",
			g_op_tab[NEXT_OP].name, OP_CAST);
	else
		mvwprintw(v->win_processes, i - v->process_offset, 20,
			"                 is looking for instruction.");
}

static void	maj_process_print(t_viewer *v, t_list *process,
				t_process **selected, int i)
{
	if (v->process_offset <= i && i - v->process_offset
		< getmaxy(v->win_processes))
	{
		if (i == v->process_selected)
			*selected = (t_process *)process->content;
		wattron(v->win_processes, COLOR_PAIR(i == v->process_selected ?
			14 : (v->vm->a.owner[PC] % 4) + 2));
		mvwprintw(v->win_processes, i - v->process_offset, 0,
			"#%-5d %2dx%-2d [%c][%c]: ", NPRO, PC / 64 + 1, PC % 64 + 1,
			PRINT_LIVE, PRINT_CARRY);
		maj_process_print_msg(v, process, i);
		wattroff(v->win_processes, COLOR_PAIR(i == v->process_selected ?
			14 : (v->vm->a.owner[PC] % 4) + 2));
	}
	if (i != v->process_selected)
	{
		wattron(v->win_arena, COLOR_BG(v->vm->a.owner[PC]));
		mvwprintw(v->win_arena, PC / 64, (PC % 64 * 3), "%.2x",
			v->vm->a.arena[PC]);
		wattroff(v->win_arena, COLOR_BG(v->vm->a.owner[PC]));
	}
}

void		maj_process(t_viewer *v)
{
	int			i;
	t_list		*process;
	t_process	*selected;

	i = 0;
	selected = 0;
	werase(v->win_processes);
	process = v->vm->process_lst;
	while (process)
	{
		maj_process_print(v, process, &selected, i);
		process = process->next;
		++i;
	}
	maj_process_selected(v, selected);
	wrefresh(v->win_processes);
	wrefresh(v->win_arena);
	maj_process_arena(v);
}
