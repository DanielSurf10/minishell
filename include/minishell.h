/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:57 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/05 00:20:00 by danbarbo         ###   ########.fr       */
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

# define RST    "\033[0m"      /* Reset to default color */
# define R      "\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */
# define ORANGE "\033[38;5;208m"
# define BLUE   "\033[38;5;27m"
# define GREEN  "\033[38;5;46m"
# define RED    "\033[38;5;196m"
# define YELLOW "\033[38;5;226m"
# define CYAN   "\033[38;5;51m"
# define PURPLE "\033[38;5;129m"
# define GREY   "\033[38;5;240m"
# define WHITE  "\033[38;5;231m"
# define BLACK  "\033[38;5;16m"
# define BOLD   "\033[1m"
# define UNDER  "\033[4m"
# define BLINK  "\033[5m"
# define REVERSE "\033[7m"

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
