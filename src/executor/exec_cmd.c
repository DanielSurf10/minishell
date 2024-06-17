/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:54:04 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/14 16:24:03 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_cmd(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	ret_code;

	pid = fork();
	execution_signals(pid);
	if (pid == 0)
	{
		fd_list_close_clear(&data->fd_list);
		if (is_built_in(tree))
			ret_code = exec_builtin(tree, data);
		else
			ret_code = exec_cmd_fork(tree, data);
		free_tree(&data->tree);
		env_clear_list(&data->envp_list);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(ret_code);
	}
	return (pid);
}
