/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:44:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/26 01:46:46 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_exec_tree	*make_tree_cmd_recursive(t_token_list *redir_list, t_token_list *args)
{
	t_exec_tree		*tree;

	tree = malloc(sizeof(t_exec_tree));
	ft_bzero(tree, sizeof(t_exec_tree));
	if (!redir_list && args)
	{
		// Não sei se faço uma cópia ou uso sem copiar
		// tree->command = args;
		tree->command = token_get_sublist(args, 0, token_list_size(args));

		tree->type = COMMAND;
	}
	else if (redir_list && redir_list->token.type != WORD && redir_list->next
		&& redir_list->next->token.type == WORD)
	{
		tree->type = redir_list->token.type;

		tree->left = malloc(sizeof(t_exec_tree));
		ft_bzero(tree->left, sizeof(t_exec_tree));
		tree->left->type = COMMAND;
		tree->left->command = token_get_sublist(redir_list, 1, 1);

		tree->right = make_tree_cmd_recursive(token_get_node_index(redir_list, 2), args);
	}
	else
	{
		free(tree);
		tree = NULL;
	}
	return (tree);
}

t_exec_tree	*make_tree_cmd(t_token_list *token_list)
{
	int				redir_counter;
	int				redir_list_size;
	t_token_list	*aux;
	t_token_list	*args;			// Não precisa dar free, to usando na árvore
	t_token_list	*redir_list;
	t_exec_tree		*tree;
	t_exec_tree		*aux_tree;

	redir_counter = 0;
	aux = token_list;
	args = NULL;
	redir_list = NULL;
	tree = NULL;
	while (aux)
	{
		if (aux->token.type >= REDIRECT_INPUT && aux->token.type <= REDIRECT_OUTPUT_APPEND)
		{
			token_add_to_list(&redir_list, NULL, aux->token.type);
			if (aux->next)
			{
				token_add_to_list(&redir_list, ft_strdup(aux->next->token.lexeme), aux->next->token.type);
				aux = aux->next;
			}
		}
		else
			token_add_to_list(&args, ft_strdup(aux->token.lexeme), aux->token.type);
		if (aux)
			aux = aux->next;
	}

// 	tree = malloc(sizeof(t_exec_tree));
// 	ft_bzero(tree, sizeof(t_exec_tree));
// 	aux_tree = tree;
// 	aux = redir_list;
// 	while (aux)
// 	{
// 		aux_tree->left = malloc(sizeof(t_exec_tree));
// 		ft_bzero(aux_tree->left, sizeof(t_exec_tree));
//
// 		aux_tree->right = malloc(sizeof(t_exec_tree));
// 		ft_bzero(aux_tree->right, sizeof(t_exec_tree));
//
// 		aux_tree->left->type = COMMAND;
// 		aux_tree->left->command = token_get_sublist(aux, 1, 1);
//
// 		if (aux)
// 			aux = aux->next;
// 	}


// 	aux = redir_list;
//
// 	tree = malloc(sizeof(t_exec_tree));
// 	ft_bzero(tree, sizeof(t_exec_tree));
// 	tree->type = token_get_node_index(redir_list, redir_counter)->token.type;
//
// 	aux_tree = tree;
//
// 	aux_tree->left = malloc(sizeof(t_exec_tree));
// 	ft_bzero(aux_tree->left, sizeof(t_exec_tree));
// 	aux_tree->left->type = COMMAND;
// 	aux_tree->left->command = token_get_sublist(redir_list, redir_counter + 1, 1);
//
// 	redir_counter += 2;
//
// 	aux_tree->right = malloc(sizeof(t_exec_tree));
// 	ft_bzero(aux_tree->right, sizeof(t_exec_tree));
// 	aux_tree->right->type = token_get_node_index(redir_list, redir_counter)->token.type;
//
// 	aux_tree = aux_tree->right;
//
// 	aux_tree->left = malloc(sizeof(t_exec_tree));
// 	ft_bzero(aux_tree->left, sizeof(t_exec_tree));
// 	aux_tree->left->type = token_get_node_index(redir_list, redir_counter)->token.type;
// 	aux_tree->left->command = token_get_sublist(redir_list, redir_counter + 1, 1);
//
// 	redir_counter += 2;
//
// 	// aux_tree->right = malloc(sizeof(t_exec_tree));
// 	// ft_bzero(aux_tree->right, sizeof(t_exec_tree));
// 	// aux_tree->right->type = token_get_node_index(redir_list, redir_counter)->token.type;
//
// 	// aux_tree = aux_tree->right;
//
// 	aux_tree->right = malloc(sizeof(t_exec_tree));
// 	ft_bzero(aux_tree->right, sizeof(t_exec_tree));
// 	aux_tree->right->type = COMMAND;
// 	aux_tree->right->command = token_get_sublist(args, 0, token_list_size(args));
//
// 	// aux_tree = aux_tree->right;
// 	// redir_counter += 2;


// 	redir_list_size = token_list_size(redir_list);
//
// 	aux = redir_list;
//
// 	tree = malloc(sizeof(t_exec_tree));
// 	ft_bzero(tree, sizeof(t_exec_tree));
//
// 	if (redir_list_size == 0)
// 	{
// 		tree->type = COMMAND;
// 		tree->command = token_get_sublist(args, 0, token_list_size(args));
// 		return (tree);
// 	}
//
// 	aux_tree = tree;
//
// 	while (redir_counter < redir_list_size)
// 	{
// 		aux_tree->type = token_get_node_index(redir_list, redir_counter)->token.type;
//
// 		aux_tree->left = malloc(sizeof(t_exec_tree));
// 		ft_bzero(aux_tree->left, sizeof(t_exec_tree));
// 		aux_tree->left->type = COMMAND;
// 		aux_tree->left->command = token_get_sublist(redir_list, redir_counter + 1, 1);
//
// 		aux_tree->right = malloc(sizeof(t_exec_tree));
// 		ft_bzero(aux_tree->right, sizeof(t_exec_tree));
//
// 		aux_tree = aux_tree->right;
// 		redir_counter += 2;
// 	}
//
// 	aux_tree->type = COMMAND;
// 	aux_tree->command = token_get_sublist(args, 0, token_list_size(args));
//
// 	// print_tree_aaa(tree);


	tree = make_tree_cmd_recursive(redir_list, args);

	return (tree);
}

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

	while (aux)
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
		// tree->type = COMMAND;
		// tree->command = invert_list(token_get_sublist(token_list, 0, token_list_size(token_list)));
		// tree->left = NULL;
		// tree->right = NULL;
		// tree->subshell = NULL;

		aux = invert_list(token_get_sublist(token_list, 0, token_list_size(token_list)));

		free(tree);

		tree = make_tree_cmd(aux);

		token_clear_list(&aux);

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
	tree->left = make_tree(sub_list_right);		// right vai pro left
	tree->right = make_tree(sub_list_left);		// Left vai pro right

	token_clear_list(&sub_list_left);
	token_clear_list(&sub_list_right);

	if (tree->left == NULL || tree->right == NULL)	// Aqui verifica a gramatica
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
