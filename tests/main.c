/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:25 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/03 11:58:00 by danbarbo         ###   ########.fr       */
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

int	exec_cmd(t_token_list *command)
{
	int	pid;
	int	ret_code;

	char	*cmd = command->token.lexeme;
	char	*argv[] = {command->token.lexeme, command->next->token.lexeme, NULL};

	pid = fork();

	if (pid == 0)
	{
		execve(cmd, argv, __environ);
		exit(1);
	}

	// Isso aqui vai sair
	waitpid(pid, &ret_code, 0);

	return (ret_code);
	// return (pid);
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

int	exec_cmd_pipe(t_token_list *command, int *pipe_fd)
{
	int	pid;

	char	*cmd = command->token.lexeme;
	char	*argv[] = {command->token.lexeme, command->next->token.lexeme, NULL};

	pid = fork();

	if (pid == 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(cmd, argv, __environ);
		exit(1);
	}

	return (pid);
}

int	exec_pipe(t_exec_tree *tree)
{
	int	ret_code;
	int	pid[2];
	int	old_fd[2];
	int	pipe_fd[2];


	if (tree->type == PIPE)
	{
		pipe(pipe_fd);
		old_fd[0] = dup(STDIN_FILENO);
		old_fd[1] = dup(STDOUT_FILENO);

		redir_out();
		exec_pipe(tree->left);

		redir_back_old_fd_out();
		redir_in();
		exec_pipe(tree->right);
		redir_back_old_fd_in();
	}
	else
	{
		exec_cmd_pipe(tree->command, pipe_fd);
		// exec_cmd(tree->right);
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

	return (ret_code);
}

int	exec_tree(t_exec_tree *tree)
{
	int	pid;
	int	ret_code = -1;

	if (tree->type == COMMAND)
	{
		// pid = exec_cmd(tree->command);
		// waitpid(pid, &ret_code, 0);

		ret_code = exec_cmd(tree->command);
	}
	else if (tree->type == AND)
		ret_code = exec_and(tree);
	else if (tree->type == OR)
		ret_code = exec_or(tree);
	else if (tree->type == SUBSHELL)
	{
		printf("Entrando no subshell\n");
		pid = fork();
		if (pid != 0)						// Pai
			waitpid(pid, &ret_code, 0);
		else								// Filho
			exit(exec_tree(tree->subshell));
		printf("Saindo no subshell\n");
	}
	else if (tree->type == PIPE)
		ret_code = exec_pipe(tree);
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
// 	tree->right->command = get_token_list("echo a");
// 	tree->right->left = NULL;
// 	tree->right->right = NULL;
//
// 	// Left left leaf
// 	tree->left->left = malloc(sizeof(t_exec_tree));
// 	tree->left->left->type = COMMAND;
// 	tree->left->left->command = get_token_list("ls");
// 	tree->left->left->left = NULL;
// 	tree->left->left->right = NULL;
//
// 	// Left right leaf
// 	tree->left->right = malloc(sizeof(t_exec_tree));
// 	tree->left->right->type = COMMAND;
// 	tree->left->right->command = get_token_list("ping");
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

	// primeiro
	tree = malloc(sizeof(t_exec_tree));
	tree->type = PIPE;
	tree->command = NULL;

	// esquerda
	tree->left = malloc(sizeof(t_exec_tree));
	tree->left->type = COMMAND;
	tree->left->command = get_token_list("/bin/ls -l");
	tree->left->left = NULL;
	tree->left->right = NULL;

	// direita
	tree->right = malloc(sizeof(t_exec_tree));
	tree->right->type = COMMAND;
	tree->right->command = get_token_list("/bin/cat -e");
	tree->right->left = NULL;
	tree->right->right = NULL;


	ret_code = exec_tree(tree);

	printf("ret code main = %d\n", ret_code);

	return (0);
}
