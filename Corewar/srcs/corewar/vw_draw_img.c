/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_draw_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:34:17 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 17:54:22 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	draw_skull(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", SKULL_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", SKULL_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", SKULL_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", SKULL_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", SKULL_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", SKULL_6);
}

void	draw_laurels(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", LAURELS_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", LAURELS_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", LAURELS_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", LAURELS_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", LAURELS_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", LAURELS_6);
}

void	draw_cup(t_viewer *v, int i)
{
	mvwprintw(v->win_champions[i], 0, 0, "%ls", CUP_1);
	mvwprintw(v->win_champions[i], 1, 0, "%ls", CUP_2);
	mvwprintw(v->win_champions[i], 2, 0, "%ls", CUP_3);
	mvwprintw(v->win_champions[i], 3, 0, "%ls", CUP_4);
	mvwprintw(v->win_champions[i], 4, 0, "%ls", CUP_5);
	mvwprintw(v->win_champions[i], 5, 0, "%ls", CUP_6);
}

void	draw_logo(t_viewer *v)
{
	mvwprintw(v->win_title, 0, 0, "%ls", L1);
	mvwprintw(v->win_title, 1, 0, "%ls", L2);
	mvwprintw(v->win_title, 2, 0, "%ls", L3);
	mvwprintw(v->win_title, 3, 0, "%ls", L4);
	mvwprintw(v->win_title, 4, 0, "%ls", L5);
	mvwprintw(v->win_title, 5, 0, "%ls", L6);
	mvwprintw(v->win_title, 6, 0, "%ls", L7);
	mvwprintw(v->win_title, 7, 0, "%ls", L8);
	mvwprintw(v->win_title, 8, 0, "%ls", L9);
	mvwprintw(v->win_title, 9, 0, "%ls", L10);
}
