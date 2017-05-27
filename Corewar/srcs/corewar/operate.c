/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 13:55:14 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/25 14:53:04 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_ar(t_vm *v, t_list *process, t_uchar *shift, t_uchar type)
{
	int		ret;
	t_uchar	label;

	label = type >> 2 ? 2 : 4;
	if ((type & 0b11) == 1)
		ret = REG[ARENA(PC + 2 + (*shift)++) - 1];
	else if ((type & 0b11) == 2)
	{
		ret = reverse_bytes(v, PC + 2 + *shift, label);
		*shift += label;
	}
	else
	{
		ret = reverse_bytes(v, PC + 2 + *shift, 2) % IDX_MOD;
		ret = reverse_bytes(v, PC + ret, 4);
		*shift += 2;
	}
	return (ret);
}

int		reverse_bytes(t_vm *v, unsigned int pc, int nbytes)
{
	unsigned char two_bytes[2];
	unsigned char four_bytes[4];

	if (nbytes == 2)
	{
		two_bytes[0] = ARENA(pc + 1);
		two_bytes[1] = ARENA(pc);
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = ARENA(pc + 3);
		four_bytes[1] = ARENA(pc + 2);
		four_bytes[2] = ARENA(pc + 1);
		four_bytes[3] = ARENA(pc);
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

void	init_next_op(t_vm *v, t_list *process)
{
	if (ARENA(PC) > 16 || ARENA(PC) <= 0)
	{
		NEXT_OP = -1;
		PC++;
		PC %= MEM_SIZE;
	}
	else
	{
		NEXT_OP = ARENA(PC) - 1;
		OP_CAST = g_op_tab[NEXT_OP].cycle - 1;
	}
}
