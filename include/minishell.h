/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:57 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/05 14:12:24 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "libft.h"

//****************************************************************************//
//                                   Colors                                   //
//****************************************************************************//

# define RST    "\001\033[0m\002"      /* Reset to default color */
# define R      "\001\033[1;31m\002"   /* Bold Red */
# define G      "\001\033[1;32m\002"   /* Bold Green */
# define Y      "\001\033[1;33m\002"   /* Bold Yellow */
# define B      "\001\033[1;34m\002"   /* Bold Blue */
# define M      "\001\033[1;35m\002"   /* Bold Magenta */
# define C      "\001\033[1;36m\002"   /* Bold Cyan */
# define W      "\001\033[1;37m\002"   /* Bold White */
# define ORANGE "\001\033[38;5;208m\002"
# define BLUE   "\001\033[38;5;27m\002"
# define GREEN  "\001\033[38;5;46m\002"
# define RED    "\001\033[38;5;196m\002"
# define YELLOW "\001\033[38;5;226m\002"
# define CYAN   "\001\033[38;5;51m\002"
# define PURPLE "\001\033[38;5;129m\002"
# define GREY   "\001\033[38;5;240m\002"
# define WHITE  "\001\033[38;5;231m\002"
# define BLACK  "\001\033[38;5;16m\002"
# define BOLD   "\001\033[1m\002"
# define UNDER  "\001\033[4m\002"
# define BLINK  "\001\033[5m\002"
# define REVERSE "\001\033[7m\002"

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

typedef struct s_envp_list	t_envp_list;
typedef struct s_exec_tree	t_exec_tree;
typedef struct termios		t_termios;

typedef struct s_minishell
{
	int			is_heredoc;
	t_envp_list	*envp_list;
	t_exec_tree	*tree;
	t_list		*fd_list;
}	t_minishell;

#endif
