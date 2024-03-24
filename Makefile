# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/03/23 21:55:45 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
NAME_BONUS	:= minishell_bonus
# CFLAGS		:= -Wextra -Wall -Werror -g3
CFLAGS		:= -g3

LIBFT_DIR	:= lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a
LIBS		:= ${LIBFT} -lreadline

HEADERS		:= -I include \
				-I ${LIBFT_DIR}/include

SRCS		:= ${shell find src -iname "*.c"}		# Não esquecer de mudar isso aqui
OBJS		:= ${SRCS:src/%.c=obj/%.o}

SRCS_BONUS	:= ${shell find src -iname "*.c"}		# Não esquecer de mudar isso aqui
OBJS_BONUS	:= ${SRCS_BONUS:src_bonus/%.c=obj/%.o}

all: ${NAME}
bonus: ${NAME_BONUS}

${NAME}: ${LIBFT} ${OBJS}
	@${CC} ${CFLAGS} ${HEADERS} ${OBJS} ${LIBS} -o ${NAME}

${NAME_BONUS}: ${LIBFT} ${OBJS_BONUS}
	@${CC} ${CFLAGS} ${HEADERS} ${OBJS_BONUS} ${LIBS} -o ${NAME_BONUS}

obj/%.o: src/%.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

obj/%.o: src_bonus/%.c
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
re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus libft
