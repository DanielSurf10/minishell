/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:25 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/04 16:43:42 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	print_tree(t_exec_tree *exec_tree)
{
	if (exec_tree == NULL)
		return ;

	print_tree(exec_tree->left);
	print_tree(exec_tree->right);

	if (exec_tree->command->token.type == AND)
		printf("&&\n");
	else
		printf("%s\n", exec_tree->command->token.lexeme);
}

int	open_redir(char *path_to_file, int type)
{
	int	fd;

	if (type == REDIRECT_INPUT)
		fd = open(path_to_file, O_RDONLY);
	else if (type == REDIRECT_OUTPUT)
		fd = open(path_to_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIRECT_OUTPUT_APPEND)
		fd = open(path_to_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

void	exec_cmd_fork(t_exec_tree *tree)
{
	int	fd_redir = 0;

	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		fd_redir = open_redir(tree->left->command->token.lexeme, tree->type);
		if (fd_redir != -1)
			exit(1);

		if (tree->type == REDIRECT_INPUT)	// Talvez hereredoc
			dup2(fd_redir, STDIN_FILENO);
		else if (tree->type == REDIRECT_OUTPUT || tree->type == REDIRECT_OUTPUT_APPEND)
			dup2(fd_redir, STDOUT_FILENO);
		close(fd_redir);
		exec_cmd_fork(tree->right);
	}
	else
	{
		char	*argv[] = {tree->command->token.lexeme, tree->command->next->token.lexeme, NULL};
		char	*cmd = tree->command->token.lexeme;
		execve(cmd, argv, __environ);
	}
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

int	main()
{
	int			ret_code;
	t_exec_tree	*tree;

	// && e ||

// 	// First branch
// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = OR;
// 	tree->command = get_token_list("||");
//
// 	// Left leaf
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = AND;
// 	tree->left->command = get_token_list("&&");
//
// 	// Right leaf
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = COMMAND;
// 	tree->right->command = get_token_list("/bin/echo a");
// 	tree->right->left = NULL;
// 	tree->right->right = NULL;
//
// 	// Left left leaf
// 	tree->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->left->type = COMMAND;
// 	tree->left->left->command = get_token_list("/bin/ls -l");
// 	tree->left->left->left = NULL;
// 	tree->left->left->right = NULL;
//
// 	// Left right leaf
// 	tree->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->type = COMMAND;
// 	tree->left->right->command = get_token_list("/bin/hostname -I");
// 	tree->left->right->left = NULL;
// 	tree->left->right->right = NULL;


	// Sub Shell

// 	// primeiro
// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = AND;
// 	// tree->command = get_token_list("&&");
// 	tree->command = NULL;
//
// 	// esquerda
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = AND;
// 	// tree->left->command = get_token_list("&&");
// 	tree->left->command = NULL;
//
// 	// direita
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = COMMAND;
// 	tree->right->command = get_token_list("/bin/echo 1");
// 	tree->right->left = NULL;
// 	tree->right->right = NULL;
//
// 	// esquerda esquerda
// 	tree->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->left->type = COMMAND;
// 	tree->left->left->command = get_token_list("/bin/echo 2");
// 	tree->left->left->left = NULL;
// 	tree->left->left->right = NULL;
//
// 	// esquerda direita
// 	tree->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->type = SUBSHELL;
// 	tree->left->right->command = NULL;
// 	tree->left->right->left = NULL;
// 	tree->left->right->right = NULL;
//
// 	// esquerda direita subshell
// 	tree->left->right->subshell = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->type = AND;
// 	// tree->left->right->subshell->command = get_token_list("&&");
// 	tree->left->right->subshell->command = NULL;
//
// 	// esquerda direita subshell esquerda
// 	tree->left->right->subshell->left = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->left->type = AND;
// 	// tree->left->right->subshell->left->command = get_token_list("&&");
// 	tree->left->right->subshell->left->command = NULL;
//
// 	// esquerda direita subshell direita
// 	tree->left->right->subshell->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->right->type = COMMAND;
// 	tree->left->right->subshell->right->command = get_token_list("/bin/echo 3");
//
// 	// esquerda direita subshell esquerda esquerda
// 	tree->left->right->subshell->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->left->left->type = AND;
// 	// tree->left->right->subshell->left->left->command = get_token_list("&&");
// 	tree->left->right->subshell->left->left->command = NULL;
//
// 	// esquerda direita subshell esquerda direita
// 	tree->left->right->subshell->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->left->right->type = SUBSHELL;
// 	tree->left->right->subshell->left->right->command = NULL;
// 	tree->left->right->subshell->left->right->left = NULL;
// 	tree->left->right->subshell->left->right->right = NULL;
//
// 	// esquerda direita subshell esquerda direita subshell
// 	tree->left->right->subshell->left->right->subshell = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->left->right->subshell->type = COMMAND;
// 	tree->left->right->subshell->left->right->subshell->command = get_token_list("/bin/echo 4");
// 	tree->left->right->subshell->left->right->subshell->left = NULL;
// 	tree->left->right->subshell->left->right->subshell->right = NULL;
//
// 	// esquerda direita subshell esquerda esquerda esquerda
// 	tree->left->right->subshell->left->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->left->left->left->type = COMMAND;
// 	tree->left->right->subshell->left->left->left->command = get_token_list("/bin/echo 5");
// 	tree->left->right->subshell->left->left->left->left = NULL;
// 	tree->left->right->subshell->left->left->left->right = NULL;
//
// 	// esquerda direita subshell esquerda esquerda direita
// 	tree->left->right->subshell->left->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->left->left->right->type = COMMAND;
// 	tree->left->right->subshell->left->left->right->command = get_token_list("/bin/echo 6");
// 	tree->left->right->subshell->left->left->right->left = NULL;
// 	tree->left->right->subshell->left->left->right->right = NULL;


	// Execve

// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = AND;
// 	tree->command = NULL;
//
// 	// Esquerda
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = COMMAND;
// 	tree->left->command = get_token_list("/bin/ls -l");
// 	tree->left->left = NULL;
// 	tree->left->right = NULL;
//
// 	// Direita
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = COMMAND;
// 	tree->right->command = get_token_list("/bin/cat todo");
// 	tree->right->left = NULL;
// 	tree->right->right = NULL;


	// Pipe

// 	// primeiro
// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = PIPE;
// 	tree->command = NULL;
//
// 	// esquerda
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = COMMAND;
// 	tree->left->command = get_token_list("/bin/ls -l");
//
// 	// direita
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = COMMAND;
// 	tree->right->command = get_token_list("/bin/cat -e");


	// pipe

// 	// primeiro
// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = PIPE;
//
// 	// esquerda
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = PIPE;
//
// 	// direita
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = COMMAND;
// 	tree->right->command = get_token_list("/bin/grep 1");
//
// 	// esquerda esquerda
// 	tree->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->left->type = COMMAND;
// 	tree->left->left->command = get_token_list("/bin/ls -l");
//
// 	// esquerda direita
// 	tree->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->type = COMMAND;
// 	tree->left->right->command = get_token_list("/bin/hostname -I");

	// pipe com subshell

// 	// primeiro
// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = PIPE;
//
// 	// esquerda
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = PIPE;
//
// 	// direito
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = COMMAND;
// 	tree->right->command = get_token_list("/bin/cat -e");
//
// 	// esquerdo esquerdo
// 	tree->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->left->type = COMMAND;
// 	tree->left->left->command = get_token_list("/bin/ls -l");
//
// 	// esquerdo direito
// 	tree->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->type = SUBSHELL;
//
// 	// esquerdo direito subshell
// 	tree->left->right->subshell = malloc(sizeof(t_exec_tree));
// 	tree->left->right->subshell->type = COMMAND;
// 	tree->left->right->subshell->command = get_token_list("/bin/grep r--");


	// pipe com subshell

// 	// primeiro
// 	tree = malloc(sizeof(t_exec_tree));
// 	tree->type = PIPE;
//
// 	// esquerda
// 	tree->left = malloc(sizeof(t_exec_tree));
// 	tree->left->type = COMMAND;
// 	tree->left->command = get_token_list("/bin/ls -l");
//
// 	// direito
// 	tree->right = malloc(sizeof(t_exec_tree));
// 	tree->right->type = SUBSHELL;
//
// 	// direito subshell
// 	tree->right->subshell = malloc(sizeof(t_exec_tree));
// 	tree->right->subshell->type = COMMAND;
// 	tree->right->subshell->command = get_token_list("/bin/cat -e");


	ret_code = exec_tree(tree);

	printf("ret code main = %d\n", ret_code);

	return (0);
}
