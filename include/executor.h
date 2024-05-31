/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/30 22:39:46 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include "lexing.h"
# include "expander.h"
# include "parsing.h"
# include "minishell.h"

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

int		exec_or(t_exec_tree *tree, t_minishell *data);
int		exec_and(t_exec_tree *tree, t_minishell *data);
int		exec_tree(t_exec_tree *tree, t_minishell *data);

int		open_redir(char *path_to_file, int type);
int		exec_cmd(t_exec_tree *tree, int fd_to_close, t_minishell *data);
void	exec_cmd_fork(t_exec_tree *tree, t_minishell *data);

#endif
