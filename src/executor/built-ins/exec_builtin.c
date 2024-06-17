/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:11:11 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/17 12:08:45 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	builtin_call(char *cmd, char **argv, t_minishell *data)
{
	int	ret_code;

	ret_code = 0;
	if (ft_strncmp(cmd, "echo", -1) == 0)
		ret_code = builtin_echo(argv);
	else if (ft_strncmp(cmd, "cd", -1) == 0)
		ret_code = builtin_cd(argv, data);
	else if (ft_strncmp(cmd, "pwd", -1) == 0)
		ret_code = builtin_pwd();
	else if (ft_strncmp(cmd, "export", -1) == 0)
		ret_code = builtin_export(argv, data);
	else if (ft_strncmp(cmd, "unset", -1) == 0)
		ret_code = builtin_unset(argv, &data->envp_list);
	else if (ft_strncmp(cmd, "env", -1) == 0)
		ret_code = builtin_env(data);
	else if (ft_strncmp(cmd, "exit", -1) == 0)
		ret_code = builtin_exit(argv, data);
	return (ret_code);
}

static void	init_exec_cmd_builtin(t_exec_tree *tree, \
	t_minishell *data, int *fd_redir)
{
	char	*cmd;

	cmd = expand_string(tree->left->command->token.lexeme, data->envp_list);
	*fd_redir = open_redir(cmd, tree->type);
	free(cmd);
}

static int	aux_exec_cmd_builtin(t_exec_tree *tree, \
	t_minishell *data, t_builtin *builtin)
{
	int	idx;
	int	ret_code;

	idx = 0;
	builtin->args_num = token_list_size(tree->command);
	builtin->argv = malloc((builtin->args_num + 1) * sizeof(char *));
	builtin->argv[builtin->args_num] = NULL;
	while (idx < builtin->args_num)
	{
		builtin->argv[idx] = expand_string(token_get_node_index(tree->command, \
			idx)->token.lexeme, data->envp_list);
		idx++;
	}
	builtin->cmd = builtin->argv[0];
	ret_code = builtin_call(builtin->cmd, builtin->argv, data);
	free_envp(builtin->argv);
	return (ret_code);
}

int	exec_cmd_builtin(t_exec_tree *tree, t_minishell *data)
{
	t_builtin	builtin;

	builtin.ret_code = 0;
	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		init_exec_cmd_builtin(tree, data, &builtin.fd_redir);
		if (builtin.fd_redir == -1)
		{
			perror(tree->left->command->token.lexeme);
			return (1);
		}
		if (tree->type == REDIRECT_INPUT)
			dup2(builtin.fd_redir, STDIN_FILENO);
		else if (tree->type == REDIRECT_OUTPUT || \
			tree->type == REDIRECT_OUTPUT_APPEND)
			dup2(builtin.fd_redir, STDOUT_FILENO);
		builtin.fd_redir = close_fd(builtin.fd_redir);
		builtin.ret_code = exec_cmd_builtin(tree->right, data);
	}
	else
		builtin.ret_code = aux_exec_cmd_builtin(tree, data, &builtin);
	return (builtin.ret_code);
}

int	exec_builtin(t_exec_tree *tree, t_minishell *data)
{
	int	ret_code;
	int	old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	ret_code = exec_cmd_builtin(tree, data);
	dup2(old_fd[0], STDIN_FILENO);
	dup2(old_fd[1], STDOUT_FILENO);
	close_pipe(old_fd);
	return (ret_code);
}
