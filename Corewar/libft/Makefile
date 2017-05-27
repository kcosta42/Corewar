# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:00:00 by kcosta            #+#    #+#              #
#    Updated: 2017/04/27 14:32:59 by kcosta           ###   ########.fr        #
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
NAME			:= libft.a
# ============================== #

# ========== Standard ========== #
CC				:= gcc
FLAGS			:= -Wall -Wextra -Werror
# ============================== #

# =========== Files ============ #
SRCS_FILES		:=	ft_printf/buffer.c		\
					ft_printf/cast_mod.c	\
					ft_printf/format.c		\
					ft_printf/ft_nblen.c	\
					ft_printf/ft_nblen_b.c	\
					ft_printf/ft_power.c	\
					ft_printf/ft_printf.c	\
					ft_printf/ft_u_nblen.c	\
					ft_printf/ft_u_power.c	\
					ft_printf/fwp_bin.c		\
					ft_printf/fwp_char.c	\
					ft_printf/fwp_hex.c		\
					ft_printf/fwp_int.c		\
					ft_printf/fwp_oct.c		\
					ft_printf/fwp_ptr.c		\
					ft_printf/fwp_u_int.c	\
					ft_printf/fwp_wchar.c	\
					ft_printf/fwp_wstr.c	\
					ft_printf/lst_arg.c		\
					ft_printf/num_field.c	\
					ft_printf/parser.c		\
					ft_printf/str_field.c	\
					get_next_line/ft_getline.c		\
					get_next_line/get_next_line.c	\
					memory/ft_bzero.c		\
					memory/ft_memalloc.c	\
					memory/ft_memccpy.c		\
					memory/ft_memchr.c		\
					memory/ft_memcmp.c		\
					memory/ft_memcpy.c		\
					memory/ft_memdel.c		\
					memory/ft_memmove.c		\
					memory/ft_memset.c		\
					print/ft_putchar.c		\
					print/ft_putchar_fd.c	\
					print/ft_putendl.c		\
					print/ft_putendl_fd.c	\
					print/ft_putnbr.c		\
					print/ft_putnbr_fd.c	\
					print/ft_putstr.c		\
					print/ft_putstr_fd.c	\
					single_linked_list/ft_lstadd.c		\
					single_linked_list/ft_lstaddback.c	\
					single_linked_list/ft_lstappend.c	\
					single_linked_list/ft_lstdel.c		\
					single_linked_list/ft_lstdelone.c	\
					single_linked_list/ft_lstinttab.c	\
					single_linked_list/ft_lstiter.c		\
					single_linked_list/ft_lstlen.c		\
					single_linked_list/ft_lstmap.c		\
					single_linked_list/ft_lstnew.c		\
					single_linked_list/ft_lstpop.c		\
					single_linked_list/ft_lstpush.c		\
					strings/ft_strcat.c		\
					strings/ft_strchr.c		\
					strings/ft_strclr.c		\
					strings/ft_strcmp.c		\
					strings/ft_strcpy.c		\
					strings/ft_strdel.c		\
					strings/ft_strdup.c		\
					strings/ft_strequ.c		\
					strings/ft_striter.c	\
					strings/ft_striteri.c	\
					strings/ft_strjoin.c	\
					strings/ft_strlcat.c	\
					strings/ft_strlen.c		\
					strings/ft_strmap.c		\
					strings/ft_strmapi.c	\
					strings/ft_strncat.c	\
					strings/ft_strncmp.c	\
					strings/ft_strncpy.c	\
					strings/ft_strnequ.c	\
					strings/ft_strnew.c		\
					strings/ft_strnstr.c	\
					strings/ft_strrchr.c	\
					strings/ft_strrev.c		\
					strings/ft_strsplit.c	\
					strings/ft_strsplitdel.c	\
					strings/ft_strstr.c		\
					strings/ft_strsub.c		\
					strings/ft_strtrim.c	\
					utils/ft_atoi.c			\
					utils/ft_isalnum.c		\
					utils/ft_isalpha.c		\
					utils/ft_isascii.c		\
					utils/ft_isdigit.c		\
					utils/ft_isdigitstr.c	\
					utils/ft_islower.c		\
					utils/ft_isprint.c		\
					utils/ft_isspace.c		\
					utils/ft_isupper.c		\
					utils/ft_itoa.c			\
					utils/ft_squeeze.c		\
					utils/ft_tolower.c		\
					utils/ft_toupper.c

HEADERS_FILES	:=	ft_fct_tab.h	\
					ft_printf.h		\
					libft.h
# ============================== #

# ========== Sources =========== #
SRCS_PATH		:= srcs/
SRCS			:= $(addprefix $(SRCS_PATH), $(SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH		:= objs/
OBJS_DIRS		:= $(addprefix $(OBJS_PATH), ft_printf/ get_next_line/ memory/ print/ single_linked_list/ strings/ utils/)
OBJS			:= $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
HEADERS			:= $(addprefix $(INCLUDES_PATH), $(HEADERS_FILES))
# ============================== #
#
.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(OBJS_DIRS) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	@ar rc -v $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	@rm -fv $(OBJS)
	@rmdir $(OBJS_DIRS) 2> /dev/null || true
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NAME)

re: fclean all
