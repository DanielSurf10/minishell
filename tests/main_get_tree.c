/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:11:12 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/25 19:59:49 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_exec_tree	*get_tree(t_token_list *token_list);
void	free_tree(t_exec_tree **tree);


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

int main()
{
	t_token_list	*token_list;
	t_exec_tree		*tree;

	token_list = get_token_list("cat < infile -e");
	tree = get_tree(token_list);

	// print_tree(tree);

	token_clear_list(&token_list);
	free_tree(&tree);
}
