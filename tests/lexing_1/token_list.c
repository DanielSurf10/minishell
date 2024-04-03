/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:27:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/02 21:01:47 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_token_list	*create_token(char *lexeme, int type)
{
	t_token_list	*new_token;

	new_token = malloc(sizeof(t_token_list));
	new_token->token.content = lexeme;
	new_token->token.type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token_list **token_list, char *lexeme, int type)
{
	t_token_list	*new_token;
	t_token_list	*last_node;

	new_token = create_token(lexeme, type);
	last_node = *token_list;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = new_token;
	else
		*token_list = new_token;
}

void	clear_token_list(t_token_list **token_list)
{
	t_token_list	*aux1;
	t_token_list	*aux2;

	if (token_list)
	{
		aux1 = *token_list;
		while (aux1)
		{
			aux2 = aux1->next;
			free(aux1->token.content);
			free(aux1);
			aux1 = aux2;
		}
		*token_list = NULL;
	}
}
