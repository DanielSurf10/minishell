/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:43:25 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/13 18:00:35 by danbarbo         ###   ########.fr       */
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
