/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:50:19 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/25 15:35:09 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_adv(t_vm *v, t_list *process, int shift)
{
	int	i;

	i = -1;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", shift, PC, PC + shift);
	while (++i < shift)
		ft_printf("%02x ", ARENA(PC + i));
	ft_printf("\n");
}

void	print_reg(t_vm *v, t_list *process, unsigned int val, int addr)
{
	char i;

	i = 4;
	while (i--)
	{
		OWNER(addr) = OWNER(PC);
		ARENA(addr--) = val & 0xFF;
		val >>= 8;
	}
}

int		check_arg(t_uchar arg, t_uchar n, t_uchar arg_nb)
{
	t_uchar	n00;
	t_uchar	n01;
	int		shift;
	int		k;

	k = 0;
	shift = 6;
	while (arg_nb--)
	{
		n01 = (n >> shift) & 0b11;
		n00 = n01 ? 1 << (n01 - 1) : 0;
		if (!(n00 & g_op_tab[arg].args[k]))
			return (0);
		k++;
		shift -= 2;
	}
	return (1);
}

int		octal_shift(t_uchar n, t_uchar label_size, t_uchar arg_nb)
{
	int shift;

	shift = 2;
	while (++arg_nb <= 4)
		n >>= 2;
	while (n)
	{
		shift += ((n & 0b11) == 0b01) ? 1 : 0;
		shift += ((n & 0b11) == 0b11) ? 2 : 0;
		shift += ((n & 0b11) == 0b10) ? label_size : 0;
		n >>= 2;
	}
	return (shift);
}
