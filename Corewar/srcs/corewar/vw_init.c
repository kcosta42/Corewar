/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:20:09 by wolrajht          #+#    #+#             */
/*   Updated: 2017/04/27 12:52:35 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	viewer_init_colors(t_viewer *v)
{
	if (has_colors() == FALSE)
	{
		viewer_free(v);
		xerror("Your terminal does not support color\n", -33);
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_BLACK, COLOR_MAGENTA);
}

static void	viewer_init_ncurses(t_viewer *v)
{
	int i;

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);
	refresh();
	create_newwin((int[4]){ARENA_L, ARENA_C, 0, 0}, ARENA_NAME,
		&v->win_arena, &v->win_arena_box);
	create_newwin((int[4]){TITLE_L, TITLE_C, 0, ARENA_C}, TITLE_NAME,
		&v->win_title, &v->win_title_box);
	create_newwin((int[4]){PROCS_L, PROCS_C, TITLE_L, ARENA_C}, PROCS_NAME,
		&v->win_processes, &v->win_processes_box);
	create_newwin((int[4]){REGIS_L, REGIS_C, TITLE_L + PROCS_L, ARENA_C},
		REGIS_NAME, &v->win_register, &v->win_register_box);
	create_newwin((int[4]){INFOS_L, INFOS_C, ARENA_L, 0}, INFOS_NAME,
		&v->win_infos, &v->win_infos_box);
	i = -1;
	while (++i < v->vm->nplayer)
		create_newwin((int[4]){CHAMP_L, CHAMP_C, LINES - (CHAMP_L),
			ARENA_C + i * CHAMP_C}, (char *)v->vm->p[i].name,
			&v->win_champions[i], &v->win_champions_box[i]);
	draw_logo(v);
	wrefresh(v->win_title);
}

void		viewer_init(t_viewer *v, t_vm *vm)
{
	setlocale(LC_ALL, "");
	v->vm = vm;
	vm->v = v;
	v->lpf = 1;
	v->fps = 32768;
	v->event_flags = FLAG_EVENT_PAUSE;
	ft_memset(v->heal_flag, 0, sizeof(int) * MAX_PLAYERS);
	v->credits_flag = 0;
	v->process_selected = 0;
	v->process_offset = 0;
	ft_memset(v->anim_state, 101, sizeof(char) * MAX_PLAYERS);
	ft_memset(v->arena_flags, 0, sizeof(int) * MEM_SIZE);
	pthread_mutex_init(&v->mutex, NULL);
	pthread_cond_init(&v->cond, NULL);
	viewer_init_ncurses(v);
	viewer_init_colors(v);
}

void		viewer_run(t_viewer *v)
{
	int		i;
	void	*ret;

	if (pthread_create(&v->th_render, NULL, &th_render_routine, v) < 0
		|| pthread_create(&v->th_core, NULL, &th_core_routine, v) < 0
		|| pthread_create(&v->th_input, NULL, &th_input_routine, v) < 0
		|| pthread_create(&v->th_timer, NULL, &th_timer_routine, v) < 0)
	{
		viewer_free(v);
		xerror("pthread_create error for th_timer\n", -33);
	}
	(void)pthread_join(v->th_core, &ret);
	(void)pthread_join(v->th_input, &ret);
	(void)pthread_join(v->th_render, &ret);
	(void)pthread_join(v->th_timer, &ret);
	i = -1;
	while (++i < v->vm->nplayer)
		(void)pthread_join(v->th_anim[i], &ret);
	viewer_free(v);
}

void		viewer_free(t_viewer *v)
{
	int i;

	delwin(v->win_arena);
	delwin(v->win_title);
	delwin(v->win_processes);
	delwin(v->win_register);
	delwin(v->win_infos);
	i = -1;
	while (++i < v->vm->nplayer)
		delwin(v->win_champions[i]);
	delwin(v->win_arena_box);
	delwin(v->win_title_box);
	delwin(v->win_processes_box);
	delwin(v->win_register_box);
	delwin(v->win_infos_box);
	i = -1;
	while (++i < v->vm->nplayer)
		delwin(v->win_champions_box[i]);
	endwin();
}
