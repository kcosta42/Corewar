/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:30:42 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/25 14:41:48 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ldi(t_vm *v, t_list *process)
{
	t_uchar	arg_nb;
	t_uchar	type;
	t_uchar	shift;
	int		val[3];

	arg_nb = 3;
	shift = 0;
	if (check_arg(9, B_OCT, arg_nb))
	{
		while (arg_nb)
		{
			type = (B_OCT >> (arg_nb-- * 2)) & 0b11;
			if (type == 1 &&
				(ARENA(PC + 2 + shift) > 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[arg_nb] = !arg_nb ? ARENA(PC + 2 + shift) - 1 :
				get_ar(v, process, &shift, type + 4);
			if (!arg_nb)
				exe_ldi(v, process, val);
		}
	}
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 2, 3));
	PC = (PC + octal_shift(B_OCT, 2, 3)) % MEM_SIZE;
}

void	op_lld(t_vm *v, t_list *process)
{
	t_uchar	arg_nb;
	int		shift;

	arg_nb = 2;
	if (check_arg(12, B_OCT, arg_nb))
	{
		if ((ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) >= 1) &&
				(ARENA(PC + 6 - ((B_OCT & 0x60) >> 5)) <= 16))
		{
			if (OCT_00(B_OCT) == 2)
				shift = reverse_bytes(v, PC + 2, 4);
			else
			{
				shift = reverse_bytes(v, PC + 2, 2);
				shift = reverse_bytes(v, PC + shift, 2);
			}
			exe_lld(v, process, shift);
		}
	}
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 4, arg_nb));
	PC = (PC + octal_shift(B_OCT, 4, arg_nb)) % MEM_SIZE;
}

void	op_lldi(t_vm *v, t_list *process)
{
	t_uchar	arg_nb;
	t_uchar	type;
	t_uchar	shift;
	int		val[3];

	arg_nb = 3;
	shift = 0;
	if (check_arg(13, B_OCT, arg_nb))
	{
		while (arg_nb)
		{
			type = (B_OCT >> (arg_nb-- * 2)) & 0b11;
			if (type == 1 &&
				(ARENA(PC + 2 + shift) > 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[arg_nb] = !arg_nb ? ARENA(PC + 2 + shift) - 1 :
				get_ar(v, process, &shift, type + 4);
			if (!arg_nb)
				exe_lldi(v, process, val);
		}
	}
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(B_OCT, 2, 3));
	PC = (PC + octal_shift(B_OCT, 2, 3)) % MEM_SIZE;
}

void	op_sti(t_vm *v, t_list *process)
{
	t_uchar	arg_nb;
	t_uchar	shift;
	int		val[3];
	t_uchar	save;

	arg_nb = 3;
	shift = 0;
	save = B_OCT;
	if (check_arg(10, B_OCT, arg_nb))
	{
		while (arg_nb--)
		{
			if (((B_OCT >> ((arg_nb + 1) * 2)) & 0b11) == 1 &&
				(ARENA(PC + 2 + shift) > 16 || !ARENA(PC + 2 + shift)))
				break ;
			val[arg_nb] = arg_nb == 2 ? ARENA(PC + 2 + shift++) - 1 :
		get_ar(v, process, &shift, ((B_OCT >> ((arg_nb + 1) * 2)) & 0b11) + 4);
			if (!arg_nb)
				exe_sti(v, process, val);
		}
	}
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_PCMOVE))
		print_adv(v, process, octal_shift(save, 2, 3));
	PC = (PC + octal_shift(save, 2, 3)) % MEM_SIZE;
}
