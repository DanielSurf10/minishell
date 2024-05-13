/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:44:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/13 16:56:00 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


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

void	print_tree(t_exec_tree *tree)
{
	if (tree == NULL)
		return ;

	if (tree->type == COMMAND)
	{
		printf("COMMAND: ");
		print_tokens(tree->command);
	}
	else
	{
		printf("TYPE: ");

		switch (tree->type)
		{
		case PIPE:
			printf("PIPE\n");
			break;

		case OR:
			printf("OR\n");
			break;

		case AND:
			printf("AND\n");
			break;

		case COMMAND:
			printf("COMMAND\n");
			break;

		case REDIRECT_INPUT:
			printf("REDIRECT_INPUT\n");
			break;

		case REDIRECT_HEREDOC:
			printf("REDIRECT_HEREDOC\n");
			break;

		case REDIRECT_OUTPUT:
			printf("REDIRECT_OUTPUT\n");
			break;

		case REDIRECT_OUTPUT_APPEND:
			printf("REDIRECT_OUTPUT_APPEND\n");
			break;

		default:
			printf("OUTRO\n");
			break;
		}

		printf("LEFT: ");
		print_tree(tree->left);
		printf("RIGHT: ");
		print_tree(tree->right);
	}
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

int main()
{
	t_token_list	*token_list;
	t_exec_tree		*tree;

	token_list = get_token_list("< infile cat | cat -e");

	tree = get_tree(token_list);

	print_tree(tree);

	token_clear_list(&token_list);
	free_tree(&tree);
}
