/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:37:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/23 13:16:22 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static int	th_core_run(t_vm *v, int cooldown)
{
	if (!v->process_lst)
	{
		v->v->credits_flag = 1;
		show_credits(v->v);
		pthread_mutex_unlock(&v->v->mutex);
		return (0);
	}
	pthread_mutex_unlock(&v->v->mutex);
	while (cooldown && v->process_lst)
	{
		update_vm(v);
		if (v->process_lst)
		{
			browse_processes_lst(v);
			if ((BCTD) || v->cycle_to_die < 0)
				kill_processes_lst(v);
		}
		--cooldown;
	}
	return (1);
}

void		*th_core_routine(void *p_data)
{
	t_viewer	*v;
	int			cooldown;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	while (1)
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		else if (v->event_flags & FLAG_EVENT_CORE
			|| v->event_flags & FLAG_EVENT_PAUSE)
			pthread_cond_wait(&v->cond, &v->mutex);
		else
		{
			cooldown = v->lpf;
			if (!th_core_run(v->vm, cooldown))
				pthread_exit(0);
			pthread_mutex_lock(&v->mutex);
			v->event_flags |= FLAG_EVENT_CORE;
			pthread_cond_broadcast(&v->cond);
		}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
