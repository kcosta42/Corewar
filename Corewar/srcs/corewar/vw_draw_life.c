/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_draw_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 09:48:18 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 15:37:13 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	draw_life_full(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_FULL_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_FULL_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_FULL_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_FULL_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_FULL_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_FULL_6);
}

void	draw_life_high(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_HIGH_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_HIGH_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_HIGH_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_HIGH_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_HIGH_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_HIGH_6);
}

void	draw_life_medium(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_MEDIUM_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_MEDIUM_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_MEDIUM_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_MEDIUM_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_MEDIUM_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_MEDIUM_6);
}

void	draw_life_low(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_LOW_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_LOW_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_LOW_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_LOW_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_LOW_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_LOW_6);
}
