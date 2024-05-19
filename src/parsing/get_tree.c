/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:44:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/18 21:03:53 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_exec_tree	*make_tree(t_token_list *token_list)
{
	int				i;
	int				and_or_indice;
	int				pipe_indice;
	// int				redir_indice;
	t_token_list	*aux;
	t_token_list	*sub_list_left;
	t_token_list	*sub_list_right;
	t_exec_tree		*tree = NULL;

	i = 0;
	and_or_indice = -1;
	pipe_indice = -1;
	// redir_indice = -1;
	aux = token_list;

	if (token_list == NULL)
		return (NULL);

	tree = malloc(sizeof(t_exec_tree));
	ft_bzero(tree, sizeof(t_exec_tree));

	while (aux != NULL)
	{
		if (and_or_indice == -1 && (aux->token.type == AND || aux->token.type == OR))
			and_or_indice = i;
		else if (pipe_indice == -1 && (aux->token.type == PIPE))
			pipe_indice = i;
		// else if (pipe_indice == -1 && (aux->token.type >= 2 && aux->token.type <= 5))
		// 	redir_indice = i;
		i++;
		aux = aux->next;
	}

	if (and_or_indice != -1)
	{
		i = and_or_indice;
	}
	else if (pipe_indice != -1)
	{
		i = pipe_indice;
	}
	// else if (redir_indice != -1)
	// {
	// 	i = redir_indice;
	// }
	else
	{
		tree->type = COMMAND;
		tree->command = invert_list(token_get_sublist(token_list, 0, token_list_size(token_list)));
		tree->left = NULL;
		tree->right = NULL;
		tree->subshell = NULL;
		return (tree);
	}

	// Isso aqui tá meio coisado, talvez eu mude dps
	tree->type = token_get_node_index(token_list, i)->token.type;

	// printf("%d\n", i);

	// if (aux->token.type == AND || aux->token.type == OR)
	// {
	// 	tree->type = aux->token.type;
	// }

	// sub_list_left = get_until_list(token_list, i);	// Criar uma sub lista até o i
	// sub_list_right = get_rest_list(token_list, i);	// Criar uma lista com o resto

	sub_list_left = token_get_sublist(token_list, 0, i);
	sub_list_right = token_get_sublist(token_list, i + 1, token_list_size(token_list));

// 	printf("right:\n");
// 	print_tokens(sub_list_left);
//
// 	printf("\nright:\n");
// 	print_tokens(sub_list_right);

	// Já que está invertido, aqui também fica invertido - ARRUMAR ISSO, inverter na atribuição
	tree->right = make_tree(sub_list_left);		// Left vai pro right
	tree->left = make_tree(sub_list_right);		// right vai pro left

	token_clear_list(&sub_list_left);
	token_clear_list(&sub_list_right);

	if (tree->right == NULL || tree->left == NULL)	// Aqui verifica a gramatica
	{
		free(tree);
		return(NULL);
	}

	tree->command = NULL;
	tree->subshell = NULL;

	return (tree);
}

t_exec_tree	*get_tree(t_token_list *token_list)
{
	t_exec_tree		*tree;
	t_token_list	*inverted_list;

	inverted_list = invert_list(token_get_sublist(token_list, 0, token_list_size(token_list)));

	tree = make_tree(inverted_list);

	token_clear_list(&inverted_list);

	return (tree);
}

void	free_tree(t_exec_tree **tree)		// árvore de graça
{
	if (*tree == NULL)
		return ;

	if ((*tree)->subshell)
		free_tree(&(*tree)->subshell);

	if ((*tree)->left)
		free_tree(&(*tree)->left);

	if ((*tree)->right)
		free_tree(&(*tree)->right);

	if ((*tree)->command)
		token_clear_list(&(*tree)->command);

	free(*tree);
	*tree = NULL;
}
