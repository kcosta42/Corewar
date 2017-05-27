/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:11:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/27 14:44:10 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "libft.h"

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef unsigned char			t_arg_type;
typedef unsigned char			t_uchar;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef	struct s_vm				t_vm;

typedef struct					s_op
{
	char						*name;
	unsigned char				nb_arg;
	t_arg_type					args[3];
	unsigned char				opcode;
	unsigned int				cycle;
	char						*description;
	unsigned char				octal;
	unsigned char				label;
	void						(*f)(t_vm *v, t_list *process);
}								t_op;

void							op_live(t_vm *v, t_list *process);
void							op_ld(t_vm *v, t_list *process);
void							op_st(t_vm *v, t_list *process);
void							op_add(t_vm *v, t_list *process);
void							op_sub(t_vm *v, t_list *process);
void							op_and(t_vm *v, t_list *process);
void							op_or(t_vm *v, t_list *process);
void							op_xor(t_vm *v, t_list *process);
void							op_zjmp(t_vm *v, t_list *process);
void							op_ldi(t_vm *v, t_list *process);
void							op_sti(t_vm *v, t_list *process);
void							op_fork(t_vm *v, t_list *process);
void							op_lld(t_vm *v, t_list *process);
void							op_lldi(t_vm *v, t_list *process);
void							op_lfork(t_vm *v, t_list *process);
void							op_aff(t_vm *v, t_list *process);

extern t_op						g_op_tab[17];

#endif
