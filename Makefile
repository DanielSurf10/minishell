# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:20:35 by danbarbo          #+#    #+#              #
#    Updated: 2024/06/18 17:03:05 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
NAME_BONUS	:= minishell_bonus
CFLAGS		:= -Wextra -Wall -Werror -g3

LIBFT_DIR	:= lib/libft
LIBFT		:= ${LIBFT_DIR}/libft.a
LIBS		:= ${LIBFT} -lreadline

HEADERS		:= -I include \
				-I ${LIBFT_DIR}/include

SRCS		:= src/expander/expand_string_here_doc.c \
				src/expander/utils.c \
				src/expander/envp_list.c \
				src/expander/expand_command.c \
				src/expander/string_list.c \
				src/expander/expand_string.c \
				src/expander/utils_envp_list.c \
				src/lexing/state.c \
				src/lexing/token_list.c \
				src/lexing/state_change_1.c \
				src/lexing/utils.c \
				src/lexing/utils_list.c \
				src/lexing/state_change_2.c \
				src/lexing/get_token_list.c \
				src/utils_main.c \
				src/executor/exec_pipe.c \
				src/executor/exec_and_or.c \
				src/executor/built-ins/exit.c \
				src/executor/built-ins/exec_builtin.c \
				src/executor/built-ins/export.c \
				src/executor/built-ins/cd.c \
				src/executor/built-ins/pwd.c \
				src/executor/built-ins/echo.c \
				src/executor/built-ins/utiils.c \
				src/executor/built-ins/env.c \
				src/executor/built-ins/unset.c \
				src/executor/built-ins/utils_export.c \
				src/executor/utils.c \
				src/executor/exec_cmd.c \
				src/executor/fd_list.c \
				src/executor/signals/signals.c \
				src/executor/signals/signal_handler.c \
				src/executor/signals/signals_macros.c \
				src/executor/exec_cmd_fork.c \
				src/executor/exec_tree.c \
				src/executor/create_argv.c \
				src/parsing/get_tree.c \
				src/parsing/make_tree_cmd.c \
				src/parsing/here_doc.c \
				src/parsing/make_tree_cmd_recursive.c \
				src/parsing/make_tree.c \
				src/main.c
OBJS		:= ${SRCS:src/%.c=obj/%.o}

SRCS_BONUS	:= src/expander/expand_string_here_doc.c \
				src/expander/utils.c \
				src/expander/envp_list.c \
				src/expander/expand_command.c \
				src/expander/string_list.c \
				src/expander/expand_string.c \
				src/expander/utils_envp_list.c \
				src/lexing/state.c \
				src/lexing/token_list.c \
				src/lexing/state_change_1.c \
				src/lexing/utils.c \
				src/lexing/utils_list.c \
				src/lexing/state_change_2.c \
				src/lexing/get_token_list.c \
				src/utils_main.c \
				src/executor/exec_pipe.c \
				src/executor/exec_and_or.c \
				src/executor/built-ins/exit.c \
				src/executor/built-ins/exec_builtin.c \
				src/executor/built-ins/export.c \
				src/executor/built-ins/cd.c \
				src/executor/built-ins/pwd.c \
				src/executor/built-ins/echo.c \
				src/executor/built-ins/utiils.c \
				src/executor/built-ins/env.c \
				src/executor/built-ins/unset.c \
				src/executor/built-ins/utils_export.c \
				src/executor/utils.c \
				src/executor/exec_cmd.c \
				src/executor/fd_list.c \
				src/executor/signals/signals.c \
				src/executor/signals/signal_handler.c \
				src/executor/signals/signals_macros.c \
				src/executor/exec_cmd_fork.c \
				src/executor/exec_tree.c \
				src/executor/create_argv.c \
				src/parsing/get_tree.c \
				src/parsing/make_tree_cmd.c \
				src/parsing/here_doc.c \
				src/parsing/make_tree_cmd_recursive.c \
				src/parsing/make_tree.c \
				src/main.c
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
	@make -C ${LIBFT_DIR} clean

fclean: clean
	@rm -f ${NAME}
	@rm -f ${NAME_BONUS}
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

readline.supp:
	@echo '{' > $@
	@echo '   ignore_libreadline_memory_errors' >> $@
	@echo '   Memcheck:Leak' >> $@
	@echo '   ...' >> $@
	@echo '   obj:*/libreadline.so.*' >> $@
	@echo '}' >> $@

re: fclean all
re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus val
