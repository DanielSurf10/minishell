# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:05:51 by danbarbo          #+#    #+#              #
#    Updated: 2024/04/16 23:21:58 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= lexing
# CFLAGS		:= -Wextra -Wall -Werror -g3
CFLAGS		:= -g3

LIBFT_DIR	:= lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a

LIBS		:= ${LIBFT} -lreadline

HEADERS		:= -I include \
				-I ${LIBFT_DIR}/include

SRCS_TOKEN	:= $(shell find src/lexing/token_list -iname "*.c") src/utils.c
OBJS_TOKEN	:= ${SRCS_TOKEN:%.c=obj/%.o}

SRCS_EXP	:= $(shell find src/lexing/expression_list -iname "*.c")
SRCS_EXP	+= SRCS_TOKEN
OBJS_EXP	:= ${SRCS_EXP:%.c=obj/%.o}

SRCS_CMD	:= $(shell find src/lexing/token_list -iname "*.c")
SRCS_CMD	+= SRCS_EXP
OBJS_CMD	:= ${SRCS_CMD:%.c=obj/%.o}

token: ${LIBFT} ${OBJS_TOKEN}
	@${CC} ${CFLAGS} ${HEADERS} tests/token/main.c ${OBJS_TOKEN} ${LIBS} -o token_test

expression: ${LIBFT} ${OBJS_EXP}
	@${CC} ${CFLAGS} ${HEADERS} tests/expression/main.c ${OBJS_EXP} ${LIBS} -o expression_test

command: ${LIBFT} ${OBJS_CMD}
	@${CC} ${CFLAGS} ${HEADERS} tests/command/main.c ${OBJS_CMD} ${LIBS} -o command_test

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
	@rm -f token_test
	@rm -f expression_test
	@rm -f command_test
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

.PHONY: token expression command clean fclean libft
