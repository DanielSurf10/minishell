/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:11:11 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/06 19:43:07 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_cmd_builtin(t_exec_tree *tree, t_minishell *data)
{
	int		i;
	int		fd_redir;
	int		args_num;
	int		ret_code;
	char	*cmd;
	char	**argv;
	char	**envp;

	ret_code = 0;
	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		cmd = expand_string(tree->left->command->token.lexeme, data->envp_list);
		fd_redir = open_redir(cmd, tree->type);	// Fazer o tratamento de erro do redirecionamento ambíguo com o wildcard
		free(cmd);
		if (fd_redir == -1)
		{
			perror(tree->left->command->token.lexeme);
			return(1);
		}

		if (tree->type == REDIRECT_INPUT)	// Talvez hereredoc
			dup2(fd_redir, STDIN_FILENO);
		else if (tree->type == REDIRECT_OUTPUT || tree->type == REDIRECT_OUTPUT_APPEND)
			dup2(fd_redir, STDOUT_FILENO);
		fd_redir = close_fd(fd_redir);
		ret_code = exec_cmd_builtin(tree->right, data);
	}
	else
	{
		i = 0;
		args_num = token_list_size(tree->command);

		argv = malloc((args_num + 1) * sizeof(char *));
		argv[args_num] = NULL;

		while (i < args_num)
		{
			argv[i] = expand_string(token_get_node_index(tree->command, i)->token.lexeme, data->envp_list);
			i++;
		}
		cmd = argv[0];

		if (ft_strncmp(cmd, "echo", -1) == 0)
			ret_code = builtin_echo(argv);
		// else if (ft_strcmp(cmd, "cd") == 0)
		// 	ret_code = builtin_cd(argv, data);
		else if (ft_strncmp(cmd, "pwd", -1) == 0)
			ret_code = builtin_pwd();
		else if (ft_strncmp(cmd, "export", -1) == 0)
			ret_code = builtin_export(argv, data);
		else if (ft_strncmp(cmd, "unset", -1) == 0)
			ret_code = builtin_unset(argv, &data->envp_list);
		else if (ft_strncmp(cmd, "env", -1) == 0)
			ret_code = builtin_env(data);
		// else if (ft_strcmp(cmd, "exit") == 0)
		// 	ret_code = builtin_exit(argv, data);
		free_envp(argv);
	}
	return (ret_code);
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
