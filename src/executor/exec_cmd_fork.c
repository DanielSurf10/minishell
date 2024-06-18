/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:23 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/18 15:27:38 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_redirects(t_exec_tree *tree, t_minishell *data)
{
	int		fd_redir;
	int		ret_code;
	char	*cmd;

	cmd = expand_string(tree->left->command->token.lexeme, data->envp_list);
	fd_redir = open_redir(cmd, tree->type);
	free(cmd);
	if (fd_redir == -1)
	{
		perror(tree->left->command->token.lexeme);
		return (1);
	}
	if (tree->type == REDIRECT_INPUT || tree->type == REDIRECT_HEREDOC)
		dup2(fd_redir, STDIN_FILENO);
	else if (tree->type == REDIRECT_OUTPUT
		|| tree->type == REDIRECT_OUTPUT_APPEND)
		dup2(fd_redir, STDOUT_FILENO);
	fd_redir = close_fd(fd_redir);
	ret_code = exec_cmd_fork(tree->right, data);
	return (ret_code);
}

int	display_error(char *cmd)
{
	int		ret_code;

	if (access(cmd, F_OK) != 0 || ft_strchr(cmd, '/') == NULL)
	{
		if (ft_strchr(cmd, '/') == NULL)
			printf("%s - Command not found\n", cmd);
		else
			printf("%s - No such file or directory\n", cmd);
		ret_code = 127;
	}
	else if (access(cmd, F_OK | X_OK) != 0 || is_directory(cmd))
	{
		ret_code = 126;
		if (is_directory(cmd))
			printf("%s - Is a directory\n", cmd);
		else
			printf("%s - Permission denied\n", cmd);
	}
	else
	{
		perror(cmd);
		ret_code = 1;
	}
	return (ret_code);
}

int	exec_execve(t_exec_tree *tree, t_minishell *data)
{
	int		ret_code;
	char	*cmd;
	char	**argv;
	char	**envp;

	argv = create_argv(tree, data);
	if (argv[0])
	{
		cmd = expand_command(argv[0], data->envp_list);
		envp = create_envp(data->envp_list);
		if (access(cmd, F_OK | X_OK) == 0
			&& ft_strchr(cmd, '/') != NULL)
			execve(cmd, argv, envp);
		ret_code = display_error(cmd);
		free(cmd);
		free_envp(envp);
	}
	else
		ret_code = 0;
	free_envp(argv);
	return (ret_code);
}

int	execute_command(t_exec_tree *tree, t_minishell *data)
{
	int		args_num;
	int		ret_code;

	ret_code = 0;
	args_num = token_list_size(tree->command);
	if (args_num != 0)
	{
		ret_code = exec_execve(tree, data);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	return (ret_code);
}

int	exec_cmd_fork(t_exec_tree *tree, t_minishell *data)
{
	int		ret_code;

	ret_code = 0;
	if (!tree)
		return (1);
	if (g_signal != 0)
		return (1);
	if (tree->type >= REDIRECT_INPUT
		&& tree->type <= REDIRECT_OUTPUT_APPEND)
		ret_code = execute_redirects(tree, data);
	else if (tree->type == SUBSHELL)
		ret_code = exec_tree(tree->subshell, data);
	else
		ret_code = execute_command(tree, data);
	return (ret_code);
}
