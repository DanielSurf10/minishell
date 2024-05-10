/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:44:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/10 20:38:32 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_token_list	*invert_list(t_token_list *head)
{
	t_token_list	*rest;

	if (head == NULL || head->next == NULL)
		return (head);
	rest = invert_list(head->next);
	head->next->next = head;
	head->next = NULL;
	return (rest);
}

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
	t_token_list	*aux;
	t_token_list	*sub_list_left;
	t_token_list	*sub_list_right;
	t_exec_tree		*tree;

	i = 0;
	aux = token_list;
	tree = malloc(sizeof(t_exec_tree));
	while (aux != NULL && aux->token.type != AND && aux->token.type != OR)
	{
		i++;
		aux = aux->next;
	}

	if (aux == NULL)
	{
		tree->type = COMMAND;
		tree->command = invert_list(token_get_sublist(token_list, 0, token_list_size(token_list)));
		tree->left = NULL;
		tree->right = NULL;
		tree->subshell = NULL;
		return (tree);
	}

	if (aux->token.type == AND || aux->token.type == OR)
	{
		tree->type = aux->token.type;
	}

	// sub_list_left = get_until_list(token_list, i);	// Criar uma sub lista até o i (TIPO AND)
	// sub_list_right = get_rest_list(token_list, i);	// Criar uma lista com o resto

	sub_list_left = token_get_sublist(token_list, 0, i);
	sub_list_right = token_get_sublist(token_list, i + 1, token_list_size(aux->next));

	// Já que está invertido, aqui também fica invertido
	tree->right = make_tree(sub_list_left);		// Left vai pro right
	tree->left = make_tree(sub_list_right);		// right vai pro left

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

void	print_tokens(t_token_list *token_list)
{
	int				i;
	t_token_list	*aux;

	i = 1;
	aux = token_list;
	printf("Tokens da lista:\n");
	while (aux)
	{
		if (aux->token.type == WORD)
			printf("\t%2d - %-22s = %s\n", i, "WORD", aux->token.lexeme);
		else if (aux->token.type == PIPE)
			printf("\t%2d - %-22s = %s\n", i, "PIPE", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_INPUT)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_INPUT", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_HEREDOC)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_HEREDOC", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_OUTPUT)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_OUTPUT", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_OUTPUT_APPEND)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_OUTPUT_APPEND", aux->token.lexeme);
		else if (aux->token.type == OR)
			printf("\t%2d - %-22s = %s\n", i, "OR", aux->token.lexeme);
		else if (aux->token.type == AND)
			printf("\t%2d - %-22s = %s\n", i, "AND", aux->token.lexeme);
		else if (aux->token.type == OPEN_PARENTHESIS)
			printf("\t%2d - %-22s = %s\n", i, "OPEN_PARENTHESIS", aux->token.lexeme);
		else if (aux->token.type == CLOSE_PARENTHESIS)
			printf("\t%2d - %-22s = %s\n", i, "CLOSE_PARENTHESIS", aux->token.lexeme);
		else
			printf("\t%2d - TOKEN NÃO RECONHECIDO = %s\n", i, aux->token.lexeme);
		i++;
		aux = aux->next;
	}
}

void	print_tree(t_exec_tree *tree)
{
	if (tree->type == COMMAND)
	{
		printf("COMMAND: ");
		print_tokens(tree->command);
	}
	else
	{
		printf("TYPE: %d\n", tree->type);
		printf("LEFT: ");
		print_tree(tree->left);
		printf("RIGHT: ");
		print_tree(tree->right);
	}
}

void	free_tree(t_exec_tree **tree)
{
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

int main()
{
	t_token_list	*token_list;
	t_exec_tree		*tree;

	token_list = get_token_list("ls | cat -e || echo oi");

	tree = get_tree(token_list);

	print_tree(tree);

	token_clear_list(&token_list);
	free_tree(&tree);
}
