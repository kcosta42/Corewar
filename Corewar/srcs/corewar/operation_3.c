/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:54:01 by bduron            #+#    #+#             */
/*   Updated: 2017/04/23 20:40:38 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | zjmp %d %s\n", NPRO, shift, CARRY ? "OK" : "FAILED");
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE)
		&& !CARRY)
		print_adv(v, process, 3);
	shift %= IDX_MOD;
	PC = CARRY == 1 ? (unsigned int)(PC + shift) % MEM_SIZE :
		(PC + 3) % MEM_SIZE;
}

void	op_fork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | fork %d (%d)\n",
				NPRO, shift, PC + (shift % IDX_MOD));
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, 3);
	add_process(v, process, (unsigned int)(PC + (shift % IDX_MOD)) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}

void	op_lfork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | lfork %d (%d)\n", NPRO, shift, PC + shift);
	if (v->display_mode == 1 && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, 3);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}
