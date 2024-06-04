/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:57 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/04 18:09:51 by danbarbo         ###   ########.fr       */
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
