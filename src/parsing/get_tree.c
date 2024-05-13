/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:44:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/13 18:12:17 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// t_token_list	*get_copy_list(t_token_list *token_list)
// {
// 	t_token_list	*new_list;
//
// 	new_list = malloc(sizeof(t_token_list));
// 	while (token_list)
// 	{
// 		token_add_to_list(&new_list, ft_strdup(token_list->token.lexeme), token_list->token.type);
// 		token_list = token_list->next;
// 	}
// 	return (new_list);
// }

// t_token_list	*get_until_list(t_token_list *token_list, int end)
// {
// 	int				i;
// 	t_token_list	*aux;
// 	t_token_list	*new_list;
//
// 	i = 0;
// 	new_list = NULL;
// 	aux = token_list;
// 	while ()
// }

// t_token_list	*get_rest_list(t_token_list *token_list, int start)
// {
// 	int				count;
// 	t_token_list	*aux;
// 	t_token_list	*new_list;
// 	t_token_list	*new_list_aux;
//
// 	count = 0;
// 	aux = token_list;
// 	while (aux && i >= count)
// 	{
// 		aux = aux->next;
// 		count++;
// 	}
// 	new_list = malloc(sizeof(t_token_list));
// 	new_list_aux = new_list;
// 	while (aux)
// 	{
// 		new_list_aux->token = aux->token;
// 		new_list_aux->next = malloc(sizeof(t_token_list));
// 		new_list_aux = new_list_aux->next;
// 		aux = aux->next;
// 	}
// 	new_list_aux = NULL;
// 	return (new_list);
// }

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
	tree = malloc(sizeof(t_exec_tree));

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

	// sub_list_left = get_until_list(token_list, i);	// Criar uma sub lista até o i (TIPO AND)
	// sub_list_right = get_rest_list(token_list, i);	// Criar uma lista com o resto

	sub_list_left = token_get_sublist(token_list, 0, i);
	sub_list_right = token_get_sublist(token_list, i + 1, token_list_size(token_list));

// 	printf("right:\n");
// 	print_tokens(sub_list_left);
//
// 	printf("\nright:\n");
// 	print_tokens(sub_list_right);

	// Já que está invertido, aqui também fica invertido
	if (sub_list_left)
		tree->right = make_tree(sub_list_left);		// Left vai pro right
	else
		tree->right = NULL;

	if (sub_list_right)
		tree->left = make_tree(sub_list_right);		// right vai pro left
	else
		tree->left = NULL;

	token_clear_list(&sub_list_left);
	token_clear_list(&sub_list_right);

	tree->command = NULL;
	tree->subshell = NULL;

	return (tree);
}

t_exec_tree	*get_tree(t_token_list *token_list)
{
	t_exec_tree	*tree;

	token_list = invert_list(token_list);

	tree = make_tree(token_list);

	token_list = invert_list(token_list);

	return (tree);
}

void	free_tree(t_exec_tree **tree)
{
	if (*tree == NULL)
		return ;

	if ((*tree)->type == COMMAND)
	{
		token_clear_list(&(*tree)->command);
	}
	else
	{
		free_tree(&(*tree)->left);
		free_tree(&(*tree)->right);
	}
	free(*tree);
}
