/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:38:00 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/23 12:05:40 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	th_input_update_infos(t_viewer *v, int input)
{
	pthread_mutex_lock(&v->mutex);
	if (input == KEY_FPS_LL)
		v->fps /= (v->fps > 4096) ? 2 : 1;
	else if (input == KEY_FPS_PP)
		v->fps *= (v->fps < 1048576) ? 2 : 1;
	else if (input == KEY_LPF_LL)
		v->lpf /= (v->lpf > 1) ? 2 : 1;
	else if (input == KEY_LPF_PP)
		v->lpf *= (v->lpf < 1000) ? 2 : 1;
	else if (input == KEY_PAUSE)
	{
		v->event_flags ^= FLAG_EVENT_PAUSE;
		pthread_cond_broadcast(&v->cond);
	}
	maj_infos_input(v);
	pthread_mutex_unlock(&v->mutex);
}

static void	th_input_update_process(t_viewer *v, int input)
{
	pthread_mutex_lock(&v->mutex);
	if (input == KEY_PROCESS_LL)
	{
		if (v->process_selected)
			--v->process_selected;
		if (v->process_selected < v->process_offset)
			--v->process_offset;
	}
	else if (input == KEY_PROCESS_PP)
	{
		if (v->process_selected < v->vm->nprocess_alive - 1)
			++v->process_selected;
		else
			v->process_selected = v->vm->nprocess_alive - 1;
		if (v->process_offset + getmaxy(v->win_processes) - 1
			< v->process_selected)
			++v->process_offset;
	}
	maj_process(v);
	pthread_mutex_unlock(&v->mutex);
}

void		*th_input_routine(void *p_data)
{
	t_viewer	*v;
	int			input;

	v = (t_viewer *)p_data;
	while (1)
	{
		if (((input = getch()) == ERR) || input == KEY_QUIT)
		{
			pthread_mutex_lock(&v->mutex);
			v->event_flags |= FLAG_EVENT_QUIT;
			pthread_cond_broadcast(&v->cond);
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		else if (!v->credits_flag)
		{
			if (input == KEY_FPS_LL || input == KEY_FPS_PP
				|| input == KEY_LPF_PP || input == KEY_LPF_LL
				|| input == KEY_PAUSE)
				th_input_update_infos(v, input);
			else if (input == KEY_PROCESS_LL || input == KEY_PROCESS_PP)
				th_input_update_process(v, input);
		}
	}
	pthread_exit(0);
}
