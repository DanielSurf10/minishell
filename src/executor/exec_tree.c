/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/14 16:44:31 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// int	open_redir(char *path_to_file, int type)
// {
// 	int	fd;
//
// 	if (type == REDIRECT_INPUT)
// 		fd = open(path_to_file, O_RDONLY);
// 	else if (type == REDIRECT_OUTPUT)
// 		fd = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (type == REDIRECT_OUTPUT_APPEND)
// 		fd = open(path_to_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	return (fd);
// }

// void	exec_cmd_fork(t_exec_tree *tree)
// {
// 	int	fd_redir = 0;
//
// 	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
// 	{
// 		fd_redir = open_redir(tree->left->command->token.lexeme, tree->type);
// 		if (fd_redir != -1)
// 			exit(1);
//
// 		if (tree->type == REDIRECT_INPUT)	// Talvez hereredoc
// 			dup2(fd_redir, STDIN_FILENO);
// 		else if (tree->type == REDIRECT_OUTPUT || tree->type == REDIRECT_OUTPUT_APPEND)
// 			dup2(fd_redir, STDOUT_FILENO);
// 		close(fd_redir);
// 		exec_cmd_fork(tree->right);
// 	}
// 	else
// 	{
// 		char	*argv[] = {tree->command->token.lexeme, tree->command->next->token.lexeme, NULL};
// 		char	*cmd = tree->command->token.lexeme;
// 		execve(cmd, argv, __environ);
// 	}
// 	exit(1);
// }

void	exec_cmd_fork(t_exec_tree *tree)
{
	char	*argv[] = {tree->command->token.lexeme, tree->command->next->token.lexeme, NULL};
	char	*cmd = tree->command->token.lexeme;

	execve(cmd, argv, __environ);
	exit(1);
}

int	exec_cmd(t_exec_tree *tree)
{
	int	pid;
// 	int	all_ok;
//
// 	char	*cmd;

// 	all_ok = 1;
// 	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
// 		all_ok = exec_redirect(tree);
//
// 	char	*argv[] = {tree->command->token.lexeme, tree->command->next->token.lexeme, NULL};
// 	cmd = tree->command->token.lexeme;

	pid = fork();

	if (pid == 0)
		exec_cmd_fork(tree);
	// {
	// 	execve(cmd, argv, __environ);
	// 	exit(1);
	// }

	return (pid);
}

int	exec_and(t_exec_tree *tree)
{
	int	ret_code;

	ret_code = exec_tree(tree->left);

	if (ret_code == 0)
		ret_code = exec_tree(tree->right);

	return (ret_code);
}

int	exec_or(t_exec_tree *tree)
{
	int	ret_code;

	ret_code = exec_tree(tree->left);

	if (ret_code != 0)
		ret_code = exec_tree(tree->right);

	return (ret_code);
}

// int	exec_cmd_pipe(t_token_list *command, int *pipe_fd)
// {
// 	int	pid;
//
// 	char	*cmd = command->token.lexeme;
// 	char	*argv[] = {command->token.lexeme, command->next->token.lexeme, NULL};
//
// 	pid = fork();
//
// 	if (pid == 0)
// 	{
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 		execve(cmd, argv, __environ);
// 		exit(1);
// 	}
//
// 	return (pid);
// }

int	exec_pipe(t_exec_tree *tree)
{
	int	ret_code = 0;
	int	pid;
	int	old_fd[2];
	int	pipe_fd[2];

	if (tree->type == PIPE)
	{
		pipe(pipe_fd);
		old_fd[0] = dup(STDIN_FILENO);
		old_fd[1] = dup(STDOUT_FILENO);

		// Comando da esquerda
		// redir_out();
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);

		exec_pipe(tree->left);

		// Comando da direita
		// redir_back_old_fd_out();
		dup2(old_fd[1], STDOUT_FILENO);
		close(old_fd[1]);

		// redir_in();
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);

		pid = exec_pipe(tree->right);

		// redir_back_old_fd_in();
		dup2(old_fd[0], STDIN_FILENO);
		close(old_fd[0]);
	}
	else if (tree->type == COMMAND)
		pid = exec_cmd(tree);
	else if (tree->type == SUBSHELL)
	{
		pid = fork();
		if (pid == 0)
			exit(exec_tree(tree->subshell));
	}


// 	old_fd[0] = dup(STDIN_FILENO);
// 	old_fd[1] = dup(STDOUT_FILENO);
//
// 	pipe(pipe_fd);
//
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	pid[0] = exec_cmd_pipe(tree->left->command, pipe_fd);
//
// 	dup2(pipe_fd[0], STDIN_FILENO);
// 	dup2(old_fd[1], STDOUT_FILENO);
// 	pid[1] = exec_cmd_pipe(tree->right->command, pipe_fd);
//
// 	dup2(old_fd[0], STDIN_FILENO);
//
// 	close(old_fd[0]);
// 	close(old_fd[1]);
//
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
//
// 	waitpid(pid[0], NULL, 0);
// 	waitpid(pid[1], &ret_code, 0);

	return (pid);
}

int	exec_tree(t_exec_tree *tree)
{
	int	pid;
	int	num[2];
	int	ret_code = -1;

	if (tree->type == COMMAND || tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		pid = exec_cmd(tree);
		waitpid(pid, &ret_code, 0);
		ret_code = (ret_code >> 8) & 0xFF;
	}
	else if (tree->type == AND)
		ret_code = exec_and(tree);
	else if (tree->type == OR)
		ret_code = exec_or(tree);
	else if (tree->type == SUBSHELL)
	{
		pid = fork();
		if (pid != 0)						// Pai
		{
			waitpid(pid, &ret_code, 0);
			ret_code = (ret_code >> 8) & 0xFF;
		}
		else								// Filho
			exit(exec_tree(tree->subshell));
	}
	else if (tree->type == PIPE)
	{
		pid = exec_pipe(tree);

		num[0] = wait(&num[1]);

		while (num[0] != -1)
		{
			if (num[0] == pid)
				ret_code = (num[1] >> 8) & 0xFF;
			num[0] = wait(&num[1]);
		}
	}
	return (ret_code);
}
