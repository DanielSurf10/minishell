/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:37:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 15:25:00 by danbarbo         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	char			*line;
	t_token_list	*token_list;

	line = readline("minishell$: ");
	// line = "ls -l";
	token_list = get_token_list(line);

	if (token_list == NULL)
		printf("Erro!");
	else
		print_tokens(token_list);

	token_clear_list(&token_list);

	return (0);
}
