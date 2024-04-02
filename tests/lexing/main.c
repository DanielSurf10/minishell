/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:37:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/01 23:53:10 by danbarbo         ###   ########.fr       */
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

t_token_list	*get_token_list(char *str)
{
	int				i;
	int				state;
	int				token_type;
	int				str_length;
	int				lexeme_length;
	char			*lexeme;
	t_token_list	*token_list;

	i = 0;
	state = 1;
	lexeme_length = 0;
	str_length = ft_strlen(str);
	token_list = NULL;
	while (i <= str_length)		// Aqui o '\0' tem que ser considerado também
	{
		state = get_next_state(state, str[i]);
		if (state != 1)
			lexeme_length += 1;

		if (state == -1)
		{
			clear_token_list(&token_list);
			break ;
		}

		if (state_is_final(state))
		{
			if (state_requires_backtrack_one_char(state))
			{
				i -= 1;
				lexeme_length -= 1;
			}
			token_type = get_token_type(state);
			lexeme = ft_substr(str, i - (lexeme_length - 1), lexeme_length);
			add_token_to_list(&token_list, lexeme, token_type);
			lexeme_length = 0;
			state = 1;
		}
		i++;
	}
	return (token_list);
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
