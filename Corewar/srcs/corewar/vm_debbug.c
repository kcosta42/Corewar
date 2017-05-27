/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_debbug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:59:57 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/27 14:46:50 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_arena(t_vm *v)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_printf(" \n");
		if (i % 64 == 0 && i != (MEM_SIZE - 1))
			ft_printf("0x%04x :", i);
		if (i % 1 == 0)
			ft_printf(" ");
		ft_printf("%02x", v->a.arena[i]);
		i++;
	}
	ft_printf(" \n");
}

/*
** void print_processes(t_vm *v)
** {
** 	t_list *tmp;
** 	int i;
**
** 	tmp = v->process_lst;
** 	i = 0;
** 	while (tmp)
** 	{
** 		ft_printf("\n============ %d ============\n", i);
** 		ft_printf("|_carry:                  %d\n",
**			((t_process *)tmp->content)->carry);
** 		ft_printf("|_pc:                     %d\n",
**			((t_process *)tmp->content)->pc);
** 		ft_printf("|_live count:             %d\n",
**			((t_process *)tmp->content)->live_count);
** 		ft_printf("|_op cast:                %d\n",
**			((t_process *)tmp->content)->op_cast);
** 		ft_printf("| r1| r2| r3| r4| r5| r6| r7| r8|
**			r9|r10|r11|r12|r13|r14|r15|r16|\n");
** 		for (int j = 0; j < REG_NUMBER; j++)
** 			ft_printf("|% 3d", ((t_process *)tmp->content)->reg[j]);
** 		ft_printf("|\n\n");
** 		tmp = tmp->next;
** 		i++;
** 	}
** }
*/

/*
** void dump(t_player p)
** {
** 	int j;
** 	int k;
** 	int c;
**
** 	j = 0;
** 	while (j <= p.prog_len)
** 	{
** 		(j == p.prog_len) ? ft_printf("%*c",
**			(((16 - j % 16) * 5) / 2), ' ') : 0;
** 		if (j % 16 == 0 || p.prog_len == j)
** 		{
** 			ft_printf("  ");
** 			k = (p.prog_len == j) ? j - j % 16 : j - 16;
** 			while (k < j && j != 0)
** 			{
** 				c = p.code[k++];
** 				ft_isprint(c) ? ft_printf("%c", c): ft_printf(".");
** 			}
** 			ft_printf("\n");
** 		}
** 		if (j % 2 == 0)
** 			ft_printf(" ");
** 		if (j < p.prog_len)
** 			ft_printf("%02x", (p.code[j]));
** 		j++;
** 	}
** }
*/

/*
** void print_arena_color(t_vm *v)
** {
**
** 	for (int i = 0; i < MEM_SIZE; i++)
** 	{
** 		if (i % 64 == 0)
** 			ft_printf("\n");
** 		if (i % 64 == 0 && i != (MEM_SIZE - 1))
** 			ft_printf("0x%04x :", i);
** 		if (i % 1 == 0)
** 			ft_printf(" ");
** 		if (v->a.owner[i] == -1)
** 			ft_printf("%02x", v->a.arena[i]);
** 		else
** 			ft_printf("\033[%dm%02x" RES, 31 + v->a.owner[i], v->a.arena[i]);
** 	}
** 	ft_printf("\n");
** }
*/

/*
** void test_print_v(t_vm *v)
** {
**
** 	ft_printf("\n[Nb players = %d]\n\n", v->nplayer);
** 	for (int i = 0; i < v->nplayer; i++)
** 	{
** 		ft_printf("nplayer = %d\n", v->p[i].nplayer);
** 		ft_printf("name = %s\n", v->p[i].name);
** 		ft_printf("comment = %s\n", (v->p[i].comment));
** 		ft_printf("pc_address = %d\n", (v->p[i].pc_address));
** 		dump(v->p[i]);
** 		ft_printf("\n\n\n");
** 	}
** 	print_arena(v);
**
** }
*/
