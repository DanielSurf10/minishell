/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:11:11 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/11 12:16:15 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static	void	builtin_call(char *cmd, char **argv, t_minishell *data)
{
	if (ft_strncmp(cmd, "echo", -1) == 0)
		builtin_echo(argv);
	else if (ft_strncmp(cmd, "cd", -1) == 0)
		builtin_cd(argv, data);
	else if (ft_strncmp(cmd, "pwd", -1) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd, "export", -1) == 0)
		builtin_export(argv, data);
	else if (ft_strncmp(cmd, "unset", -1) == 0)
		builtin_unset(argv, &data->envp_list);
	else if (ft_strncmp(cmd, "env", -1) == 0)
		builtin_env(data);
	else if (ft_strncmp(cmd, "exit", -1) == 0)
		builtin_exit(argv, data);
}

static	void	init_exec_cmd_builtin(t_exec_tree *tree, \
	t_minishell *data, int *fd_redir)
{
	char	*cmd;

	cmd = expand_string(tree->left->command->token.lexeme, data->envp_list);
	*fd_redir = open_redir(cmd, tree->type);
	free(cmd);
}

static	void	aux_exec_cmd_builtin(t_exec_tree *tree, \
	t_minishell *data, t_builtin *builtin)
{
	int	idx;

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
	builtin_call(builtin->cmd, builtin->argv, data);
	free_envp(builtin->argv);
}

int	exec_cmd_builtin(t_exec_tree *tree, t_minishell *data)
{
	t_builtin	builtin;
	int			idx;

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
		aux_exec_cmd_builtin(tree, data, &builtin);
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
