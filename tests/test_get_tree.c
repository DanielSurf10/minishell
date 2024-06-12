/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:11:12 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/11 18:44:48 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	print_tabs(int count)
{
	int	i;

	i = 0;
	while (count > i)
	{
		printf("\t");
		i++;
	}
}

void	print_tokens(t_token_list *token_list, int tab_count)
{
	int				i;
	t_token_list	*aux;

	i = 1;
	aux = token_list;

	if (!aux)
	{
		print_tabs(tab_count + 1);
		printf(" 1 - (NULL)\n");
	}

	while (aux)
	{
		print_tabs(tab_count + 1);
		if (aux->token.type == WORD)
			printf("%2d - %s = %s\n", i, "WORD", aux->token.lexeme);
		else if (aux->token.type == PIPE)
			printf("%2d - %s = %s\n", i, "PIPE", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_INPUT)
			printf("%2d - %s = %s\n", i, "REDIRECT_INPUT", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_HEREDOC)
			printf("%2d - %s = %s\n", i, "REDIRECT_HEREDOC", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_OUTPUT)
			printf("%2d - %s = %s\n", i, "REDIRECT_OUTPUT", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_OUTPUT_APPEND)
			printf("%2d - %s = %s\n", i, "REDIRECT_OUTPUT_APPEND", aux->token.lexeme);
		else if (aux->token.type == OR)
			printf("%2d - %s = %s\n", i, "OR", aux->token.lexeme);
		else if (aux->token.type == AND)
			printf("%2d - %s = %s\n", i, "AND", aux->token.lexeme);
		else if (aux->token.type == OPEN_PARENTHESIS)
			printf("%2d - %s = %s\n", i, "OPEN_PARENTHESIS", aux->token.lexeme);
		else if (aux->token.type == CLOSE_PARENTHESIS)
			printf("%2d - %s = %s\n", i, "CLOSE_PARENTHESIS", aux->token.lexeme);
		else
			printf("%2d - TOKEN NÃO RECONHECIDO = %s\n", i, aux->token.lexeme);
		i++;
		aux = aux->next;
	}
}

void	print_tree(t_exec_tree *tree, int tab_count)
{
	if (tree == NULL)
		return ;

	print_tabs(tab_count);
	printf("TYPE: ");

	if (tree->type == COMMAND)
	{
		printf("COMMAND:\n");
		print_tokens(tree->command, tab_count);
	}
	else
	{
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

		case SUBSHELL:
			printf("SUBSHELL\n");
			break;

		default:
			printf("OUTRO\n");
			break;
		}

		if (tree->left)
		{
			print_tabs(tab_count);
			printf("LEFT:\n");
			print_tree(tree->left, tab_count + 1);
		}
		if (tree->right)
		{
			print_tabs(tab_count);
			printf("RIGHT:\n");
			print_tree(tree->right, tab_count + 1);
		}
		if (tree->subshell)
		{
			print_tabs(tab_count);
			printf("SUBSHELL:\n");
			print_tree(tree->subshell, tab_count + 1);
		}
	}
}

volatile int	g_signal;

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **envp)
{
	t_token_list	*token_list;
	t_exec_tree		*tree;
	t_minishell		data;

	tree = NULL;
	ft_memset(&data, 0, sizeof(data));
	data.envp_list = env_create_list(envp);
	env_insert_node(&data.envp_list, "?", "0");

	token_list = get_token_list(argv[1]);
	tree = get_tree(token_list, &data);

	if (tree)
		print_tree(tree, 0);
	else
		printf("Sintaxe error!\n");

	token_clear_list(&token_list);
	free_tree(&tree);
}
