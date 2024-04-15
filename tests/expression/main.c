/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:13:04 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/15 18:01:20 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include <readline/history.h>
#include <readline/readline.h>

void	print_tokens(t_token_list *token_list)
{
	int				i;
	t_token_list	*aux;

	i = 1;
	aux = token_list;
	while (aux)
	{
		if (aux->token.type == WORD)
			printf("\t\t%2d - %-22s = %s\n", i, "WORD", aux->token.lexeme);
		else if (aux->token.type == PIPE)
			printf("\t\t%2d - %-22s = %s\n", i, "PIPE", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_INPUT)
			printf("\t\t%2d - %-22s = %s\n", i, "REDIRECT_INPUT", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_HEREDOC)
			printf("\t\t%2d - %-22s = %s\n", i, "REDIRECT_HEREDOC", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_OUTPUT)
			printf("\t\t%2d - %-22s = %s\n", i, "REDIRECT_OUTPUT", aux->token.lexeme);
		else if (aux->token.type == REDIRECT_OUTPUT_APPEND)
			printf("\t\t%2d - %-22s = %s\n", i, "REDIRECT_OUTPUT_APPEND", aux->token.lexeme);
		else if (aux->token.type == OR)
			printf("\t\t%2d - %-22s = %s\n", i, "OR", aux->token.lexeme);
		else if (aux->token.type == AND)
			printf("\t\t%2d - %-22s = %s\n", i, "AND", aux->token.lexeme);
		else if (aux->token.type == OPEN_PARENTHESIS)
			printf("\t\t%2d - %-22s = %s\n", i, "OPEN_PARENTHESIS", aux->token.lexeme);
		else if (aux->token.type == CLOSE_PARENTHESIS)
			printf("\t\t%2d - %-22s = %s\n", i, "CLOSE_PARENTHESIS", aux->token.lexeme);
		else
			printf("\t\t%2d - TOKEN NÃO RECONHECIDO = %s\n", i, aux->token.lexeme);
		i++;
		aux = aux->next;
	}
}

void	print_cmds(t_cmd_list *cmd_list)
{
	int			i;
	t_cmd_list	*aux;

	i = 0;
	aux = cmd_list;
	while (aux)
	{
		if (aux->command.type == WORD)
			printf("\t%2d - %-22s\n", i, "WORD");
		else if (aux->command.type == PIPE)
			printf("\t%2d - %-22s\n", i, "PIPE");
		else
			printf("\t%2d - TOKEN NÃO RECONHECIDO\n", i);
		print_tokens(aux->command.token_list);
		i++;
		aux = aux->next;
	}
}

void	print_expression(t_exp_list *exp_list)
{
	int				i;
	t_exp_list		*aux;

	i = 1;
	aux = exp_list;
	printf("Tokens da lista:\n");
	while (aux)
	{
		if (aux->expression.type == WORD)
		{
			printf("\t%2d - %-22s\n", i, "WORD");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == PIPE)
		{
			printf("\t%2d - %-22s\n", i, "PIPE");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == REDIRECT_INPUT)
		{
			printf("\t%2d - %-22s\n", i, "REDIRECT_INPUT");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == REDIRECT_HEREDOC)
		{
			printf("\t%2d - %-22s\n", i, "REDIRECT_HEREDOC");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == REDIRECT_OUTPUT)
		{
			printf("\t%2d - %-22s\n", i, "REDIRECT_OUTPUT");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == REDIRECT_OUTPUT_APPEND)
		{
			printf("\t%2d - %-22s\n", i, "REDIRECT_OUTPUT_APPEND");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == OR)
		{
			printf("\t%2d - %-22s\n", i, "OR");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == AND)
		{
			printf("\t%2d - %-22s\n", i, "AND");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == OPEN_PARENTHESIS)
		{
			printf("\t%2d - %-22s\n", i, "OPEN_PARENTHESIS");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == CLOSE_PARENTHESIS)
		{
			printf("\t%2d - %-22s\n", i, "CLOSE_PARENTHESIS");
			print_cmds(aux->expression.cmd_list);
		}
		else if (aux->expression.type == EXPRESSION)
		{
			printf("\t%2d - %-22s\n", i, "EXPRESSION");
			print_cmds(aux->expression.cmd_list);
		}
		else
		{
			printf("\t%2d - TOKEN NÃO RECONHECIDO\n", i);
			print_cmds(aux->expression.cmd_list);
		}
		i++;
		aux = aux->next;
	}
}

int	main(int argc, char *argv[])
{
	char			*line;
	t_token_list	*token_list;
	t_exp_list		*exp_list;

	line = readline("minishell$: ");
	token_list = get_token_list(line);
	exp_list = get_exp_list(token_list);

	if (token_list == NULL)
		printf("Erro!");
	else
		print_expression(exp_list);

	token_clear_list(&token_list);
	exp_clear_list(&exp_list);

	return (0);
}
