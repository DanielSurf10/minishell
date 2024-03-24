# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 19:29:07 by danbarbo          #+#    #+#              #
#    Updated: 2024/03/23 21:40:04 by danbarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
FLAGS	= -Wall -Wextra -Werror -c
INCLUDE	= include

SRC	= ${addprefix src/, \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_read_all.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c \
		}
OBJ	= ${SRC:src/%.c=obj/%.o}

all: ${NAME}
${NAME}: ${OBJ}
	@ar rcs ${NAME} ${OBJ}

obj/%.o: src/%.c
	@mkdir -p obj
	@${CC} ${FLAGS} -I ${INCLUDE} $< -o $@
	@printf "Compiling ${notdir $@}\n"

clean:
	@rm -rf obj
	@printf "Deleting object files\n"

fclean: clean
	@rm -f ${NAME}
	@printf "Deleting ${NAME}\n"

re: fclean all
rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus
