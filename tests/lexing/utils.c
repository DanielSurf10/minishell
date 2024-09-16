/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:40:03 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 21:42:13 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_token_list_equal(t_token_list *expected, t_token_list *result)
{
	while (expected && result)
	{
		if (expected->token.type != result->token.type)
			return (0);
		if ((expected->token.type == WORD && result->token.type == WORD)
			&& ft_strncmp(expected->token.lexeme, result->token.lexeme, -1) != 0)
			return (0);
		expected = expected->next;
		result = result->next;
	}
	if (expected || result)
		return (0);
	return (1);
}

void	print_tokens(t_token_list *token_list)
{
	int				i;
	t_token_list	*aux;

	i = 1;
	aux = token_list;
	if (!aux)
	{
		printf("\tEmpty list\n");
		return ;
	}
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
		else
			printf("\t%2d - TOKEN NÃO RECONHECIDO = %s\n", i, aux->token.lexeme);
		i++;
		aux = aux->next;
	}
}

void	print_result(int num_test, t_token_list *expected, t_token_list *result)
{
	if (is_token_list_equal(expected, result))
		printf(PURPLE "%2d" RST " - " GREEN "[ ✓ ]\n" RST, num_test);
	else
	{
		printf(PURPLE "%2d" RST " - " RED "[ ✗ ]\n" RST, num_test);
		printf("Expected:\n");
		print_tokens(expected);
		printf("Result:\n");
		print_tokens(result);
	}
}

void	add_on_list(t_token_list **token_list, int type, char *lexeme)
{
	t_token			token;
	t_token_list	*new;
	t_token_list	*last;

	token.lexeme = ft_strdup(lexeme);
	token.type = type;
	new = malloc(sizeof(t_token_list));
	new->token = token;
	new->next = NULL;

	last = *token_list;
	while (last && last->next)
		last = last->next;

	if (last)
		last->next = new;
	else
		*token_list = new;
}
