/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/23 20:47:11 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_vm *v, t_list *process)
{
	int live;

	LIVE++;
	v->nlive_bctd++;
	live = reverse_bytes(v, PC + 1, 4);
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | live %d\n", NPRO, live);
	is_player(v, live);
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, 5);
	PC += 5;
	PC %= MEM_SIZE;
	LIVE_SINCE = -1;
}

void	op_ld(t_vm *v, t_list *process)
{
	int shift;

	if (OCT_01(B_OCT) == 1 && (OCT_00(B_OCT) == 2 || OCT_00(B_OCT) == 3))
	{
		if ((ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) >= 1) &&
			(ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) <= 16))
		{
			if (OCT_00(B_OCT) == 2)
				shift = reverse_bytes(v, PC + 2, 4);
			else
			{
				shift = reverse_bytes(v, PC + 2, 2);
				shift %= IDX_MOD;
				shift = reverse_bytes(v, PC + shift, 4);
			}
			REG[ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) - 1] = shift;
			if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
				ft_printf("P %4d | ld %d r%d\n",
				NPRO, shift, ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)));
			CARRY = shift ? 0 : 1;
		}
	}
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 4, 2));
	PC = (PC + octal_shift(B_OCT, 4, 2)) % MEM_SIZE;
}

void	op_st(t_vm *v, t_list *process)
{
	int				shift;
	t_uchar			tmp;

	tmp = B_OCT;
	if (OCT_00(B_OCT) == 1 && ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16)
	{
		if (OCT_01(B_OCT) == 1 && ARENA(PC + 3) >= 1 && ARENA(PC + 3) <= 16)
		{
			REG[ARENA(PC + 3) - 1] = REG[ARENA(PC + 2) - 1];
			if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
				ft_printf("P %4d | st r%d %d\n",
						NPRO, ARENA(PC + 2), ARENA(PC + 3));
		}
		else if (OCT_01(B_OCT) == 0b11)
		{
			shift = reverse_bytes(v, PC + 3, 2);
			if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
				ft_printf("P %4d | st r%d %d\n", NPRO, ARENA(PC + 2), shift);
			print_reg(v, process, (unsigned int)(REG[ARENA(PC + 2) - 1]),
					PC + (shift % IDX_MOD) + 3);
		}
	}
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(tmp, 4, 2));
	PC = (PC + octal_shift(tmp, 4, 2)) % MEM_SIZE;
}

void	op_aff(t_vm *v, t_list *process)
{
	if (OCT_00(B_OCT) == 1 && ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16)
		if (v->display_mode == 5 && (v->verbose_param & FLAG_VERBOSE_AFF))
			ft_printf("Aff: %d\n", (t_uchar)REG[ARENA(PC + 2) - 1]);
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 4, 1));
	PC = (PC + octal_shift(B_OCT, 4, 1)) % MEM_SIZE;
}
