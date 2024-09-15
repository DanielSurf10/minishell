# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/09/15 14:14:27 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
# FLAGS		:= -Wextra -Wall -Werror -g3
FLAGS		:= -g3

LIBFT_DIR	:= lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a
LIBS		:= ${LIBFT} -lreadline

HEADERS		:= -I include \
				-I ${LIBFT_DIR}/include

SRCS		:= ${shell find src -iname "*.c" ! -name "main.c"}
OBJS		:= ${SRCS:src/%.c=obj/%.o}

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	@${CC} ${FLAGS} ${HEADERS} ${OBJS} src/main.c ${LIBS} -o ${NAME}

obj/%.o: src/%.c ${shell find include -iname "*.h"}
	@mkdir -p ${dir $@}
	@${CC} ${FLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

${LIBFT}:
	@make -C ${LIBFT_DIR} all

clean:
	@rm -rf obj
	@make -C ${LIBFT_DIR} clean

fclean: clean
	@rm -f ${NAME}
	@make -C ${LIBFT_DIR} fclean

val: readline.supp all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

vall: readline.supp all
	@valgrind -q --suppressions=readline.supp \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}

readline.supp:
	@echo '{' > $@
	@echo '   ignore_libreadline_memory_errors' >> $@
	@echo '   Memcheck:Leak' >> $@
	@echo '   ...' >> $@
	@echo '   obj:*/libreadline.so.*' >> $@
	@echo '}' >> $@

token: ${OBJS}
	@${CC} ${FLAGS} ${HEADERS} ${OBJS} tests/lexing/main.c ${LIBS} -o token_test
	@./token_test

re: fclean all

.PHONY: all clean fclean re val vall
