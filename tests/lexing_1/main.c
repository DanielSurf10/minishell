/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:37:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/02 20:57:16 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

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
			printf("\t%2d - %-22s = %s\n", i, "WORD", aux->token.content);
		else if (aux->token.type == PIPE)
			printf("\t%2d - %-22s = %s\n", i, "PIPE", aux->token.content);
		else if (aux->token.type == REDIRECT_INPUT)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_INPUT", aux->token.content);
		else if (aux->token.type == REDIRECT_HEREDOC)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_HEREDOC", aux->token.content);
		else if (aux->token.type == REDIRECT_OUTPUT)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_OUTPUT", aux->token.content);
		else if (aux->token.type == REDIRECT_OUTPUT_APPEND)
			printf("\t%2d - %-22s = %s\n", i, "REDIRECT_OUTPUT_APPEND", aux->token.content);
		else if (aux->token.type == OR)
			printf("\t%2d - %-22s = %s\n", i, "OR", aux->token.content);
		else if (aux->token.type == AND)
			printf("\t%2d - %-22s = %s\n", i, "AND", aux->token.content);
		else if (aux->token.type == OPEN_PARENTHESIS)
			printf("\t%2d - %-22s = %s\n", i, "OPEN_PARENTHESIS", aux->token.content);
		else if (aux->token.type == CLOSE_PARENTHESIS)
			printf("\t%2d - %-22s = %s\n", i, "CLOSE_PARENTHESIS", aux->token.content);
		else
			printf("\t%2d - TOKEN NÃO RECONHECIDO = %s\n", i, aux->token.content);
		i++;
		aux = aux->next;
	}
}

int	main(int argc, char *argv[])
{
	char			*line;
	t_token_list	*token_list;

	line = readline("minishell$: ");
	token_list = get_token_list(line);

	if (token_list == NULL)
		printf("Erro!");
	else
		print_tokens(token_list);

	clear_token_list(&token_list);

	return (0);
}
