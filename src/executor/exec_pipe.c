/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:50:59 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/14 16:24:10 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	prepare_and_execute_pipe(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	old_fd[2];
	int	pipe_fd[2];

	pipe(pipe_fd);
	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	fd_list_add_fd(&data->fd_list, old_fd[0]);
	fd_list_add_fd(&data->fd_list, old_fd[1]);
	fd_list_add_fd(&data->fd_list, pipe_fd[0]);
	fd_list_add_fd(&data->fd_list, pipe_fd[1]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	exec_pipe(tree->left, data);
	dup2(old_fd[1], STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	pid = exec_pipe(tree->right, data);
	dup2(old_fd[0], STDIN_FILENO);
	return (pid);
}

static int	exec_pipe_subshell(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	ret_code;

	pid = fork();
	if (pid == 0)
	{
		fd_list_close_clear(&data->fd_list);
		ret_code = exec_tree(tree->subshell, data);
		free_tree(&data->tree);
		env_clear_list(&data->envp_list);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(ret_code);
	}
	return (pid);
}

int	exec_pipe(t_exec_tree *tree, t_minishell *data)
{
	int			ret_code;
	int			pid;

	pid = -1;
	ret_code = 0;
	if (g_signal != 0)
		return (1);
	if (tree->type == PIPE)
		pid = prepare_and_execute_pipe(tree, data);
	else if (tree->type == COMMAND
		|| (tree->type >= REDIRECT_INPUT
			&& tree->type <= REDIRECT_OUTPUT_APPEND))
		pid = exec_cmd(tree, data);
	else if (tree->type == SUBSHELL)
		pid = exec_pipe_subshell(tree, data);
	return (pid);
}
