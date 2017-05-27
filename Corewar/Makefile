# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 12:10:08 by kcosta            #+#    #+#              #
#    Updated: 2017/04/27 14:37:25 by kcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========== Colors =========== #
CLEAR			:= "\033[2K"
UP				:= "\033[A"
EOC				:= "\033[0;0m"
BLACK			:= "\033[0;30m"
RED				:= "\033[0;31m"
GREEN			:= "\033[0;32m"
YELLOW			:= "\033[0;33m"
BLUE			:= "\033[0;34m"
PURPLE			:= "\033[0;35m"
CYAN			:= "\033[0;36m"
WHITE			:= "\033[0;37m"
# ============================== #

# ========== Editable ========== #
ASM				:= asm
COREWAR			:= corewar
# ============================== #

# ========== Standard ========== #
CC				:= gcc
FLAGS			:= -g -Wall -Wextra -Werror
# ============================== #

# =========== Files ============ #
ASM_SRCS_FILES		:=	op.c			\
						asm.c			\
						deasm.c			\
						asm_utils.c		\
						lexer.c			\
						label.c			\
						label_init.c	\
						label_utils.c	\
						parser.c		\
						parser_init.c	\
						parser_header.c	\
						scanner.c		\
						fixed_io.c		\
						deasm_manage.c
CORE_SRCS_FILES		:=	corewar.c \
						get_players.c \
						get_players_errors.c \
						vm_parsing.c \
						vm_init_free.c \
						load_arena.c \
						vm_debbug.c \
						vm_game.c \
						operate.c \
						operation_1.c \
						operation_2.c \
						operation_2b.c \
						operation_3.c \
						operation_4.c \
						operation_4b.c \
						op_shift.c \
						op.c \
						vw_draw_img.c \
						vw_draw_life.c \
						vw_draw_tools.c \
						vw_init_win.c \
						vw_init.c \
						vw_maj_process.c \
						vw_maj_win.c \
						vw_th_anim.c \
						vw_th_core.c \
						vw_th_input.c \
						vw_th_render.c \
						vw_th_timer.c
ASM_HEADERS_FILES	:=	op.h		\
						parser.h	\
						scanner.h	\
						lexer.h		\
						label.h		\
						asm.h		\
						fixed_io.h	\
						deasm.h
CORE_HEADERS_FILES	:=	op.h		\
			 			corewar.h	\
						ft_fct_tab.h
# ============================== #

# ========== Sources =========== #
ASM_PATH		:= srcs/asm/
CORE_PATH		:= srcs/corewar/
ASM_SRCS		:= $(addprefix $(ASM_PATH), $(ASM_SRCS_FILES))
CORE_SRCS		:= $(addprefix $(CORE_PATH), $(CORE_SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH			:= objs/
ASM_OBJS_PATH		:= objs/asm/
CORE_OBJS_PATH		:= objs/corewar/
ASM_OBJS		:= $(addprefix $(ASM_OBJS_PATH), $(ASM_SRCS_FILES:.c=.o))
CORE_OBJS 		:= $(addprefix $(CORE_OBJS_PATH), $(CORE_SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
ASM_HEADERS		:= $(addprefix $(INCLUDES_PATH), $(ASM_HEADERS_FILES))
CORE_HEADERS	:= $(addprefix $(INCLUDES_PATH), $(CORE_HEADERS_FILES))
# ============================== #

# ========== Libraries ========= #
LIBFT_PATH		:= libft/
LIBFT_INCLUDES	:= -I libft/includes
LIBFT			:= -L $(LIBFT_PATH) -lft -lncurses -lpthread
# ============================== #

.PHONY: all libft clean fclean re

all: libft $(ASM) $(COREWAR)

libft:
	@make -C $(LIBFT_PATH)

$(ASM_OBJS_PATH)%.o: $(ASM_PATH)%.c $(ASM_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(ASM_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(CORE_OBJS_PATH)%.o: $(CORE_PATH)%.c $(CORE_HEADERS) $(LIBFT_PATH)libft.a
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(CORE_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(ASM): $(ASM_OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(ASM_OBJS) -o $@

$(COREWAR): $(CORE_OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(CORE_OBJS) -o $@

clean:
	@make -C $(LIBFT_PATH) clean &> /dev/null
	@rm -fv $(ASM_OBJS) $(CORE_OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@make -C $(LIBFT_PATH) fclean &> /dev/null
	@rm -fv $(ASM) $(COREWAR)

re: fclean all
