/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_draw_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:09:07 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/23 11:16:36 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void		heal(t_viewer *v, int i)
{
	t_anim *a;

	if (!(a = (t_anim *)ft_memalloc(sizeof(t_anim))))
		return ;
	a->v = v;
	a->i = i;
	v->heal_flag[i] = 1;
	if (pthread_create(&v->th_anim[i], NULL, &th_anim_routine, a) < 0)
	{
		viewer_free(v);
		xerror("pthread_create error for th_anim[]\n", -33 + i);
	}
}

static void	update_anim(t_viewer *v, int i, char state)
{
	if (state != v->anim_state[i] && state < v->anim_state[i])
	{
		v->anim_state[i] = state;
		werase(v->win_champions[i]);
		wattron(v->win_champions[i], COLOR_FG(i));
		if (state == LIFE_LOW)
			draw_life_low(v, i);
		else if (state == LIFE_MEDIUM)
			draw_life_medium(v, i);
		else if (state == LIFE_HIGH)
			draw_life_high(v, i);
		else if (state == LIFE_FULL)
			draw_life_full(v, i);
		wattroff(v->win_champions[i], COLOR_FG(i));
		wrefresh(v->win_champions[i]);
	}
}

void		maj_lifes(t_viewer *v)
{
	int i;
	int state;

	i = -1;
	while (++i < v->vm->nplayer)
	{
		if (!v->heal_flag[i]
			&& v->vm->p[i].last_live_cycle <=
				(v->vm->ncycle - v->vm->ncycle_mod))
		{
			state = 100 * (v->vm->cycle_to_die - v->vm->ncycle_mod)
				/ v->vm->cycle_to_die;
			if (state < LIFE_LOW)
				update_anim(v, i, LIFE_LOW);
			else if (state < LIFE_MEDIUM)
				update_anim(v, i, LIFE_MEDIUM);
			else if (state < LIFE_HIGH)
				update_anim(v, i, LIFE_HIGH);
			else
				update_anim(v, i, LIFE_FULL);
		}
	}
}

void		show_credits(t_viewer *v)
{
	int i;

	i = -1;
	while (++i < v->vm->nplayer)
	{
		wattroff(v->win_champions[i], A_BOLD);
		werase(v->win_champions[i]);
		if (v->vm->last_live_id == i)
		{
			wattron(v->win_champions[i], COLOR_PAIR(5));
			draw_cup(v, i);
			wattron(v->win_champions[i], COLOR_PAIR(5));
		}
		else
		{
			wattron(v->win_champions[i], COLOR_PAIR(1));
			draw_skull(v, i);
			wattroff(v->win_champions[i], COLOR_PAIR(1));
		}
		wrefresh(v->win_champions[i]);
	}
}
