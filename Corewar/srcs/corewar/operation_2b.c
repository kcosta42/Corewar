/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_22.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 21:00:05 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/23 21:06:15 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exe_and(t_vm *v, t_list *process, int val[3])
{
	REG[val[0]] = val[1] & val[2];
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | and %d %d r%d\n", NPRO, val[2], val[1], val[0] + 1);
	CARRY = REG[val[0]] ? 0 : 1;
}

void	exe_or(t_vm *v, t_list *process, int val[3])
{
	REG[val[0]] = val[1] | val[2];
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | or %d %d r%d\n", NPRO, val[2], val[1], val[0] + 1);
	CARRY = REG[val[0]] ? 0 : 1;
}

void	exe_xor(t_vm *v, t_list *process, int val[3])
{
	REG[val[0]] = val[1] ^ val[2];
	if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_OPERATIONS))
		ft_printf("P %4d | xor %d %d r%d\n", NPRO, val[2], val[1], val[0] + 1);
	CARRY = REG[val[0]] ? 0 : 1;
}
