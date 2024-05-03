# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:05:51 by danbarbo          #+#    #+#              #
#    Updated: 2024/05/03 09:42:12 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= executor
# CFLAGS		:= -Wextra -Wall -Werror -g3
CFLAGS		:= -g3

LIBFT_DIR	:= lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a

LIBS		:= ${LIBFT} -lreadline

HEADERS		:= -I include \
				-I ${LIBFT_DIR}/include

SRCS		:= $(shell find src -iname "*.c")
OBJS		:= ${SRCS:%.c=obj/%.o}
SRC_MAIN	:= tests/main.c
OBJ_MAIN	:= obj/main.o

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS} ${OBJ_MAIN}
	@cc ${HEADERS} ${OBJ_MAIN} ${OBJS} ${LIBFT} -o ${NAME}

obj/%.o: %.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

obj/main.o: tests/main.c
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
#	@make -C ${LIBFT_DIR} fclean

re: fclean all

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

.PHONY: all clean fclean libft
