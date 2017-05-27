/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fct_tab.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:13:41 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/27 14:22:17 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FCT_TAB_H
# define FT_FCT_TAB_H
# include "ft_printf.h"

t_fct		g_fct_tab[] =
{
	{'s', &print_str},
	{'S', &print_str},
	{'p', &print_ptr},
	{'d', &print_int},
	{'D', &print_int},
	{'b', &print_bin},
	{'B', &print_bin},
	{'i', &print_int},
	{'o', &print_oct},
	{'O', &print_oct},
	{'u', &print_uns_int},
	{'U', &print_uns_int},
	{'x', &print_hex},
	{'X', &print_hex},
	{'c', &print_char},
	{'C', &print_char},
	{'n', &get_len},
	{0, NULL}
};

#endif
