/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/23 11:16:36 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	th_anim_run(t_viewer *v, int i, int step)
{
	if (!v->credits_flag)
	{
		if (step % 2)
			wattron(v->win_champions[i], A_BOLD);
		else
			wattroff(v->win_champions[i], A_BOLD);
		draw_life_full(v, i);
		wrefresh(v->win_champions[i]);
	}
}

void		*th_anim_routine(void *p_data)
{
	t_anim		*a;
	int			step;

	a = (t_anim *)p_data;
	step = 8;
	pthread_mutex_lock(&a->v->mutex);
	werase(a->v->win_champions[a->i]);
	wattron(a->v->win_champions[a->i], COLOR_FG(a->i));
	pthread_mutex_unlock(&a->v->mutex);
	while (step--)
	{
		pthread_mutex_lock(&a->v->mutex);
		th_anim_run(a->v, a->i, step);
		pthread_mutex_unlock(&a->v->mutex);
		usleep(70000);
	}
	pthread_mutex_lock(&a->v->mutex);
	wattroff(a->v->win_champions[a->i], A_BOLD);
	wattroff(a->v->win_champions[a->i], COLOR_FG(a->i));
	a->v->heal_flag[a->i] = 0;
	pthread_mutex_unlock(&a->v->mutex);
	free(a);
	pthread_exit(0);
}
