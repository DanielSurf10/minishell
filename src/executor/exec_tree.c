/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/28 01:46:52 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
	int		i;
	int		fd_redir;
	int		args_num;
	int		ret_code;
	char	*cmd;
	char	**argv;

	if (!tree)
		exit(1);
	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		fd_redir = open_redir(tree->left->command->token.lexeme, tree->type);	// Fazer o tratamento de erro do redirecionamento ambíguo com o wildcard
		if (fd_redir == -1)
		{
			free_tree(&tree);
			exit(3);		// 3 só para testes, colocar 1 depois
		}

		if (tree->type == REDIRECT_INPUT)	// Talvez hereredoc
			dup2(fd_redir, STDIN_FILENO);
		else if (tree->type == REDIRECT_OUTPUT || tree->type == REDIRECT_OUTPUT_APPEND)
			dup2(fd_redir, STDOUT_FILENO);
		close(fd_redir);
		exec_cmd_fork(tree->right);
	}
	else if (tree->type == SUBSHELL)
	{
		ret_code = exec_tree(tree->subshell);
		free_tree(&tree);
		exit(ret_code);
	}
	else
	{
		i = 0;
		args_num = token_list_size(tree->command);

		if (args_num != 0)			// Se não tiver commando mas tiver alguma coisa, tipo redirect ele retorna 0 no exit
		{
			argv = malloc((args_num + 1) * sizeof(char *));
			argv[args_num] = NULL;

			while (i < args_num)
			{
				// argv[i] = expand_word(token_get_node_index(tree->command, i));
				argv[i] = ft_strdup(token_get_node_index(tree->command, i)->token.lexeme);
				i++;
			}
			// cmd = expand_command(argv[0]);
			cmd = argv[0];

			execve(cmd, argv, __environ);
			free_envp(argv);
		}
		else
		{
			free_tree(&tree);
			exit(0);
		}
	}
	free_tree(&tree);
	exit(1);
}

// void	exec_cmd_fork(t_exec_tree *tree)
// {
// 	int		i;
// 	int		args_num;
// 	char	*cmd;
// 	char	**argv;
//
// 	i = 0;
// 	args_num = token_list_size(tree->command);
// 	argv = malloc((args_num + 1) * sizeof(char *));
// 	argv[args_num] = NULL;
//
// 	while (i < args_num)
// 	{
// 		// argv[i] = expand_word(token_get_node_index(tree->command, i));
// 		argv[i] = ft_strdup(token_get_node_index(tree->command, i)->token.lexeme);
// 		i++;
// 	}
// 	cmd = argv[0];
//
// 	execve(cmd, argv, __environ);
// 	exit(1);
// }

int	exec_cmd(t_exec_tree *tree)
{
	int	pid;

	pid = fork();

	if (pid == 0)
		exec_cmd_fork(tree);

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
		pipe(pipe_fd);						// Resover o leak de fd desses 3 aqui
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
	else if (tree->type == COMMAND
		|| tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
		pid = exec_cmd(tree);
	else if (tree->type == SUBSHELL)
	{
		// ret_code = exec_tree(tree->subshell);	// NÃO É ISSO
													// Precisa retornar o PID

		pid = fork();
		if (pid == 0)
		{
			ret_code = exec_tree(tree->subshell);
			free_tree(&tree);
			exit(ret_code);
		}
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
	int	pid_pipe;
	int	num[2];
	int	ret_code;

	if (tree == NULL)
		return (-1);		// Mudar isso aqui para 1 ou alguma coisa sla
	ret_code = 2;			// Mudar esse aqui tb, para algo legal
	if (tree->type == COMMAND
		|| tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		pid = exec_cmd(tree);
		waitpid(pid, &ret_code, 0);
		ret_code = (ret_code >> 8) & 0xFF;
	}
	else if (tree->type == AND && tree->left && tree->right)
		ret_code = exec_and(tree);
	else if (tree->type == OR && tree->left && tree->right)
		ret_code = exec_or(tree);
	else if (tree->type == SUBSHELL && tree->subshell)
	{
		pid = fork();
		if (pid != 0)						// Pai
		{
			waitpid(pid, &ret_code, 0);
			ret_code = (ret_code >> 8) & 0xFF;
		}
		else								// Filho
		{
			ret_code = exec_tree(tree->subshell);
			free_tree(&tree);
			exit(ret_code);
		}
	}
	else if (tree->type == PIPE && tree->left && tree->right)
	{
// 		pid_pipe = fork();
//
// 		if (pid_pipe == 0)
// 		{
			pid = exec_pipe(tree);

			num[0] = wait(&num[1]);

			while (num[0] != -1)
			{
				if (num[0] == pid)
					ret_code = (num[1] >> 8) & 0xFF;
				num[0] = wait(&num[1]);
			}
		// 	exit(ret_code);
		// }
		// waitpid(pid_pipe, &ret_code, 0);
		// ret_code = (ret_code >> 8) & 0xFF;
	}
	return (ret_code);
}