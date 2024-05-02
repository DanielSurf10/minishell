/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:25 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/02 12:38:09 by danbarbo         ###   ########.fr       */
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
	printf("%s\n", command->token.lexeme);

	if (ft_strncmp("ping", command->token.lexeme, -1) == 0)
		return (1);

	return (0);
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

int	exec_tree(t_exec_tree *tree)
{
	int	pid;
	int	ret_code = -1;

	if (tree->type == COMMAND)
		ret_code = exec_cmd(tree->command);
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
	return (ret_code);
}

int	main()
{
	int			ret_code;
	t_exec_tree	*tree;


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


	// primeiro
	tree = malloc(sizeof(t_exec_tree));
	tree->type = AND;
	// tree->command = get_token_list("&&");
	tree->command = NULL;

	// esquerda
	tree->left = malloc(sizeof(t_exec_tree));
	tree->left->type = AND;
	// tree->left->command = get_token_list("&&");
	tree->left->command = NULL;

	// direita
	tree->right = malloc(sizeof(t_exec_tree));
	tree->right->type = COMMAND;
	tree->right->command = get_token_list("pwd");
	tree->right->left = NULL;
	tree->right->right = NULL;

	// esquerda esquerda
	tree->left->left = malloc(sizeof(t_exec_tree));
	tree->left->left->type = COMMAND;
	tree->left->left->command = get_token_list("pwd");
	tree->left->left->left = NULL;
	tree->left->left->right = NULL;

	// esquerda direita
	tree->left->right = malloc(sizeof(t_exec_tree));
	tree->left->right->type = SUBSHELL;
	tree->left->right->command = NULL;
	tree->left->right->left = NULL;
	tree->left->right->right = NULL;

	// esquerda direita subshell
	tree->left->right->subshell = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->type = AND;
	// tree->left->right->subshell->command = get_token_list("&&");
	tree->left->right->subshell->command = NULL;

	// esquerda direita subshell esquerda
	tree->left->right->subshell->left = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->left->type = AND;
	// tree->left->right->subshell->left->command = get_token_list("&&");
	tree->left->right->subshell->left->command = NULL;

	// esquerda direita subshell direita
	tree->left->right->subshell->right = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->right->type = COMMAND;
	tree->left->right->subshell->right->command = get_token_list("pwd");

	// esquerda direita subshell esquerda esquerda
	tree->left->right->subshell->left->left = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->left->left->type = AND;
	// tree->left->right->subshell->left->left->command = get_token_list("&&");
	tree->left->right->subshell->left->left->command = NULL;

	// esquerda direita subshell esquerda direita
	tree->left->right->subshell->left->right = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->left->right->type = SUBSHELL;
	tree->left->right->subshell->left->right->command = NULL;
	tree->left->right->subshell->left->right->left = NULL;
	tree->left->right->subshell->left->right->right = NULL;

	// esquerda direita subshell esquerda direita subshell
	tree->left->right->subshell->left->right->subshell = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->left->right->subshell->type = COMMAND;
	tree->left->right->subshell->left->right->subshell->command = get_token_list("cd ..");
	tree->left->right->subshell->left->right->subshell->left = NULL;
	tree->left->right->subshell->left->right->subshell->right = NULL;

	// esquerda direita subshell esquerda esquerda esquerda
	tree->left->right->subshell->left->left->left = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->left->left->left->type = COMMAND;
	tree->left->right->subshell->left->left->left->command = get_token_list("cd ..");
	tree->left->right->subshell->left->left->left->left = NULL;
	tree->left->right->subshell->left->left->left->right = NULL;

	// esquerda direita subshell esquerda esquerda direita
	tree->left->right->subshell->left->left->right = malloc(sizeof(t_exec_tree));
	tree->left->right->subshell->left->left->right->type = COMMAND;
	tree->left->right->subshell->left->left->right->command = get_token_list("pwd");
	tree->left->right->subshell->left->left->right->left = NULL;
	tree->left->right->subshell->left->left->right->right = NULL;


	ret_code = exec_tree(tree);

	printf("ret code main = %d\n", ret_code);

	return (0);
}
