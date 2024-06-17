/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/17 12:15:46 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_simple_command(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	ret_code;

	if (is_built_in(tree))
		ret_code = exec_builtin(tree, data);
	else
	{
		pid = exec_cmd(tree, data);
		waitpid(pid, &ret_code, 0);
		ret_code = get_return_value(ret_code);
	}
	return (ret_code);
}

static int	execute_subshell(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	ret_code;

	ret_code = 0;
	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, &ret_code, 0);
		ret_code = get_return_value(ret_code);
	}
	else
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
	return (ret_code);
}

static int	execute_and_wait_pipe(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	ret_code;
	int	num[2];

	pid = exec_pipe(tree, data);
	fd_list_close_clear(&data->fd_list);
	ret_code = 0;
	while (1)
	{
		num[0] = wait(&num[1]);
		if (num[0] == -1)
			break ;
		if (num[0] == pid)
			ret_code = get_return_value(num[1]);
	}
	return (ret_code);
}

int	exec_tree(t_exec_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = 2;
	if (tree == NULL)
		return (2);
	if (g_signal == SIGINT)
		return (130);
	if (tree->type == COMMAND
		|| (tree->type >= REDIRECT_INPUT
			&& tree->type <= REDIRECT_OUTPUT_APPEND))
		ret_code = execute_simple_command(tree, data);
	else if (tree->type == AND && tree->left && tree->right)
		ret_code = exec_and(tree, data);
	else if (tree->type == OR && tree->left && tree->right)
		ret_code = exec_or(tree, data);
	else if (tree->type == SUBSHELL && tree->subshell)
		ret_code = execute_subshell(tree, data);
	else if (tree->type == PIPE && tree->left && tree->right)
		ret_code = execute_and_wait_pipe(tree, data);
	if (g_signal == SIGINT)
		ret_code = 130;
	return (ret_code);
}
