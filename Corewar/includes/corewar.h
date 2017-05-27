/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:16:21 by bduron            #+#    #+#             */
/*   Updated: 2017/04/27 14:54:04 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bctd = Between CYCLES_TO_DIE
*/

#ifndef COREWAR_H
# define COREWAR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"
# include "viewer.h"

# define COREWAR_EXEC_MAGIC_L 0xf383ea
# define ARENA(x)	v->a.arena[(unsigned int)(x) % MEM_SIZE]
# define OWNER(x)	v->a.owner[(unsigned int)(x) % MEM_SIZE]

# define PC			(((t_process *)process->content)->pc)
# define NPRO		(((t_process *)process->content)->nprocess)
# define CARRY		(((t_process *)process->content)->carry)
# define REG		(((t_process *)process->content)->reg)
# define NEXT_OP	(((t_process *)process->content)->next_op)
# define OP_CAST	(((t_process *)process->content)->op_cast)
# define LIVE		(((t_process *)process->content)->live_count)
# define LIVE_SINCE	(((t_process *)process->content)->live_since)
# define BCTD	(v->ncycle_mod % v->cycle_to_die == 0 && v->ncycle_mod != 0)
# define B_OCT		(ARENA(PC + 1))

# define RES "\x1B[0m"

# define OCT_03(x)	(x & 0b11)
# define OCT_02(x)	((x & 0b1100) >> 2)
# define OCT_01(x)	((x & 0b110000) >> 4)
# define OCT_00(x)	((x & 0b11000000) >> 6)

# define FLAG_OPT_VERBOSE 1
# define FLAG_OPT_DUMP 2
# define FLAG_OPT_NCURSES 4

# define DISPLAY (v->display_mode == 1)
# define FLAG_VERBOSE_LIVES 1
# define FLAG_VERBOSE_CYCLES 2
# define FLAG_VERBOSE_OPERATIONS 4
# define FLAG_VERBOSE_DEATH 8
# define FLAG_VERBOSE_PCMOVE 16
# define FLAG_VERBOSE_AFF 32

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
	char			owner[MEM_SIZE];
	char			type[MEM_SIZE];
}					t_arena;

typedef struct		s_process
{
	int				nprocess;
	int				carry;
	int				reg[REG_NUMBER];
	int				pc;
	int				op_cast;
	int				live_count;
	int				live_since;
	unsigned char	next_op;
}					t_process;

typedef struct		s_player
{
	int				nplayer;
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	code[CHAMP_MAX_SIZE];
	int				prog_len;
	int				exec_magic;
	int				pc_address;
	int				nblive;
	int				last_live_cycle;
}					t_player;

typedef struct s_viewer	t_viewer;

typedef struct		s_vm
{
	t_list			*process_lst;
	t_arena			a;
	t_player		p[MAX_PLAYERS];
	int				nplayer;
	int				nprocess;
	int				nprocess_alive;
	int				last_live_id;
	int				ncycle;
	int				ncycle_mod;
	int				nlive_bctd;
	int				cycle_to_die;
	int				ncheck;
	int				is_ctd_modified;
	int				display_mode;
	t_viewer		*v;
	unsigned int	opt_flags;
	int				dump_param;
	int				nplayer_cust;
	int				verbose_param;
}					t_vm;

void				print_help();
void				parse_opt(int argc, char **argv, t_vm *v);

void				is_player(t_vm *v, int live);
void				save_player(char *file, t_vm *v, int i, int num);
void				get_player(char **argv, int i, t_vm *v);
void				get_player_custom(char **argv, int i, t_vm *v);
int					is_corewar_execmagic(char *file);
int					get_prog_size(char *file);
int					is_valid_player(char *file);
int					is_cor_file(char *file);
void				load_arena(t_vm *v);
void				load_champions(t_vm *v);
void				load_processes(t_vm *v);
void				vm_init(t_vm *v);
t_list				*kill_head_lst(t_vm *v, t_list *process);
t_list				*kill_elem_lst(t_vm *v, t_list *process,
														t_list **previous);
void				exe_and(t_vm *v, t_list *process, int val[3]);
void				exe_or(t_vm *v, t_list *process, int val[3]);
void				exe_xor(t_vm *v, t_list *process, int val[3]);
void				exe_lld(t_vm *v, t_list *process, int shift);
void				exe_ldi(t_vm *v, t_list *process, int val[3]);
void				exe_lldi(t_vm *v, t_list *process, int val[3]);
void				exe_sti(t_vm *v, t_list *process, int val[3]);

void				print_adv(t_vm *v, t_list *process, int shift);
void				update_vm(t_vm *v);
void				run_game(t_vm *v);
void				browse_processes_lst(t_vm *v);
void				kill_processes_lst(t_vm *v);
void				init_next_op(t_vm *v, t_list *process);
void				print_reg(t_vm *v, t_list *process,
												unsigned int val, int addr);
int					get_ar(t_vm *v, t_list *process,
												t_uchar *shift, t_uchar type);
int					octal_shift(t_uchar n, t_uchar label_size, t_uchar arg_nb);
int					reverse_bytes(t_vm *v, unsigned int pc, int nbytes);
int					check_arg(t_uchar arg, t_uchar n, t_uchar arg_nb);
void				add_process(t_vm *v, t_list *process, unsigned int son_pc);

void				xerror(char *error_msg, int error_id);

/*
** debug
*/
void				dump(t_player p);
void				print_arena(t_vm *v);
void				test_print_v(t_vm *v);
void				print_processes(t_vm *v);

#endif
