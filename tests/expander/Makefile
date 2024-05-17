# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/05/17 14:38:21 by leobarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= expander.a
# CFLAGS		:= -Wextra -Wall -Werror -g3
CFLAGS		:= -g3

LIBFT_DIR	:= ../../lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a
LIBS		:= ${LIBFT} -lreadline

HEADERS		:= -I ../include \
				-I ../../include \
				-I ${LIBFT_DIR}/include

SRCS		:= utils.c
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
