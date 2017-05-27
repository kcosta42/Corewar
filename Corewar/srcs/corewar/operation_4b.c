/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_4b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 21:00:05 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/25 14:50:44 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exe_ldi(t_vm *v, t_list *process, int val[3])
{
	REG[val[0]] = reverse_bytes(v, PC + (val[1] + val[2]) % IDX_MOD, 4);
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | ldi %d %d r%d\n       | -> load from %d + %d = %d"
		" (with pc and mod %d)\n", NPRO,
		val[2], val[1], val[0] + 1, val[2], val[1], val[2] + val[1], PC +
		((val[1] + val[2]) % IDX_MOD));
}

void	exe_lldi(t_vm *v, t_list *process, int val[3])
{
	REG[val[0]] = reverse_bytes(v, PC + val[1] + val[2], 4);
	CARRY = REG[val[0]] ? 0 : 1;
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | lldi %d %d r%d\n       | -> load from %d + %d = %d"
		" (with pc %d)\n", NPRO, val[2], val[1], val[0] + 1,
		val[2], val[1], val[2] + val[1], PC + val[2] + val[1]);
}

void	exe_lld(t_vm *v, t_list *process, int shift)
{
	REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = shift;
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | lld %d r%d\n", NPRO, shift,
		ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)));
	CARRY = shift ? 0 : 1;
}

void	exe_sti(t_vm *v, t_list *process, int val[3])
{
	print_reg(v, process, REG[val[2]], PC + ((val[0] + val[1]) % IDX_MOD) + 3);
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | sti r%d %d %d\n       | -> store to %d + %d = %d"
		" (with pc and mod %d)\n", NPRO, val[2] + 1, val[1], val[0], val[1],
		val[0], val[0] + val[1], PC + ((val[0] + val[1]) % IDX_MOD));
}
