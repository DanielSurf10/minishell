# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/04/15 18:01:35 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= lexing_2.a
# CFLAGS		:= -Wextra -Wall -Werror -g3
CFLAGS		:= -g3

LIBFT_DIR	:= ../../lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a

LIBS		:= ${LIBFT} ${LEX_1} -lreadline

HEADERS		:= -I ../include \
				-I ../../include \
				-I ${LIBFT_DIR}/include

SRCS		:= ../lexing_1/get_token_list.c ../lexing_1/state.c ../lexing_1/state_change_1.c ../lexing_1/state_change_2.c ../lexing_1/token_list.c ../lexing_1/utils.c \
				exp_list.c get_exp_list.c state.c state_change.c utils.c
OBJS		:= ${SRCS:%.c=obj/%.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
#	@ar rcs ${NAME} obj/*.o
	@${CC} ${CFLAGS} ${HEADERS} main.c ${OBJS} ${LIBS} -o ../../a.out

obj/%.o: %.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

${LIBFT}:
	@make -C ${LIBFT_DIR} all

clean:
	@rm -rf obj
#	@make -C ${LIBFT_DIR} clean

fclean: clean
	@rm -f ${NAME}
	@rm -f ${NAME_BONUS}
#	@make -C ${LIBFT_DIR} fclean

val: all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

valb: all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean re libft
