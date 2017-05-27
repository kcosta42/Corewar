/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2017/04/25 17:35:29 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	t_vm		vm;
	t_viewer	v;

	vm_init(&vm);
	parse_opt(argc, argv, &vm);
	if (!vm.nplayer)
		print_help();
	vm.display_mode = (vm.opt_flags & FLAG_OPT_NCURSES) ? 2 : 3;
	vm.display_mode = (vm.opt_flags & FLAG_OPT_VERBOSE) ? 1 : vm.display_mode;
	load_arena(&vm);
	if (vm.display_mode == 2)
	{
		viewer_init(&v, &vm);
		viewer_run(&v);
	}
	else
		run_game(&vm);
	return (0);
}
