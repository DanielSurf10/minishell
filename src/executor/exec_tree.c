/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/11 18:43:44 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	open_redir(char *path_to_file, int type)
{
	int	fd;

	if (type == REDIRECT_INPUT || type == REDIRECT_HEREDOC)
		fd = open(path_to_file, O_RDONLY);
	else if (type == REDIRECT_OUTPUT)
		fd = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIRECT_OUTPUT_APPEND)
		fd = open(path_to_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

int	exec_cmd_fork(t_exec_tree *tree, t_minishell *data)
{
	int		i;
	int		fd_redir;
	int		args_num;
	int		ret_code;
	char	*cmd;
	char	**argv;
	char	**envp;

	ret_code = 0;
	if (!tree)
		return (1);
	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		cmd = expand_string(tree->left->command->token.lexeme, data->envp_list);
		fd_redir = open_redir(cmd, tree->type);
		free(cmd);
		if (fd_redir == -1)
		{
			perror(tree->left->command->token.lexeme);
			return(1);
		}

		if (tree->type == REDIRECT_INPUT || tree->type == REDIRECT_HEREDOC)
			dup2(fd_redir, STDIN_FILENO);
		else if (tree->type == REDIRECT_OUTPUT || tree->type == REDIRECT_OUTPUT_APPEND)
			dup2(fd_redir, STDOUT_FILENO);
		fd_redir = close_fd(fd_redir);
		ret_code = exec_cmd_fork(tree->right, data);
	}
	else if (tree->type == SUBSHELL)
		ret_code = exec_tree(tree->subshell, data);
	else
	{
		i = 0;
		args_num = token_list_size(tree->command);

		if (args_num != 0)
		{
			argv = malloc((args_num + 1) * sizeof(char *));
			argv[args_num] = NULL;

			while (i < args_num)
			{
				argv[i] = expand_string(token_get_node_index(tree->command, i)->token.lexeme, data->envp_list);
				i++;
			}
			cmd = expand_command(argv[0], data->envp_list);
			envp = create_envp(data->envp_list);

			if (access(cmd, F_OK | X_OK) == 0 && ft_strchr(cmd, '/') != NULL)
				execve(cmd, argv, envp);

			if (access(cmd, F_OK) != 0 || ft_strchr(cmd, '/') == NULL)
			{
				perror(cmd);
				ret_code = 127;
			}
			else if (access(cmd, F_OK | X_OK) != 0)
			{
				perror(cmd);
				ret_code = 126;
			}
			else
			{
				perror(cmd);
				ret_code = 1;
			}
			free(cmd);
			free_envp(argv);
			free_envp(envp);
		}
	}
	return (ret_code);
}

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
		exit(ret_code);
	}
	return (pid);
}

int	exec_and(t_exec_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = exec_tree(tree->left, data);

	if (ret_code == 0)
		ret_code = exec_tree(tree->right, data);

	return (ret_code);
}

int	exec_or(t_exec_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = exec_tree(tree->left, data);

	if (ret_code != 0)
		ret_code = exec_tree(tree->right, data);

	return (ret_code);
}

int	exec_pipe(t_exec_tree *tree, t_minishell *data)
{
	int			ret_code;
	int			pid;
	int			old_fd[2];
	int			pipe_fd[2];

	pid = -1;
	ret_code = 0;
	if (tree->type == PIPE)
	{
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
	}
	else if (tree->type == COMMAND
		|| (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND))
		pid = exec_cmd(tree, data);
	else if (tree->type == SUBSHELL)
	{

		pid = fork();
		if (pid == 0)
		{
			fd_list_close_clear(&data->fd_list);
			ret_code = exec_tree(tree->subshell, data);
			free_tree(&data->tree);
			env_clear_list(&data->envp_list);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			exit(ret_code);
		}
	}

	return (pid);
}

int	exec_tree(t_exec_tree *tree, t_minishell *data)
{
	int	pid;
	int	num[2];
	int	ret_code;

	ret_code = 2;
	if (tree == NULL)
		return (2);
	if (g_signal == SIGINT)
		return (130);
	if (tree->type == COMMAND
		|| (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND))
	{
		if (is_built_in(tree))
			ret_code = exec_builtin(tree, data);
		else
		{
			pid = exec_cmd(tree, data);
			waitpid(pid, &ret_code, 0);
			ret_code = get_return_value(ret_code);
		}
	}
	else if (tree->type == AND && tree->left && tree->right)
		ret_code = exec_and(tree, data);
	else if (tree->type == OR && tree->left && tree->right)
		ret_code = exec_or(tree, data);
	else if (tree->type == SUBSHELL && tree->subshell)
	{
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
			exit(ret_code);
		}
	}
	else if (tree->type == PIPE && tree->left && tree->right)
	{

			pid = exec_pipe(tree, data);
			fd_list_close_clear(&data->fd_list);

			while (1)
			{
				num[0] = wait(&num[1]);

				if (num[0] == -1)
					break ;

				if (num[0] == pid)
					ret_code = get_return_value(num[1]);
			}

	}
	if (g_signal == SIGINT)
		ret_code = 130;
	return (ret_code);
}
