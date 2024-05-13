/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/13 17:54:43 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "lexing.h"

typedef struct s_exec_tree
{
	int					type;
	t_token_list		*command;
	struct s_exec_tree	*subshell;
	struct s_exec_tree	*left;
	struct s_exec_tree	*right;
}	t_exec_tree;

int	exec_cmd(t_exec_tree *tree);
int	exec_and(t_exec_tree *tree);
int	exec_or(t_exec_tree *tree);
int	exec_tree(t_exec_tree *tree);

int	open_redir(char *path_to_file, int type);
void	exec_cmd_fork(t_exec_tree *tree);


#endif
