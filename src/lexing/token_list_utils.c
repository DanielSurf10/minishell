/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:49:09 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/14 16:50:29 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	token_clear_list(t_token_list **token_list)
{
	t_token_list	*aux1;
	t_token_list	*aux2;

	if (token_list)
	{
		aux1 = *token_list;
		while (aux1)
		{
			aux2 = aux1->next;
			if (aux1->token.lexeme)
				free(aux1->token.lexeme);
			free(aux1);
			aux1 = aux2;
		}
		*token_list = NULL;
	}
}

int	token_list_size(t_token_list *token_list)
{
	int				i;
	t_token_list	*aux;

	i = 0;
	aux = token_list;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

t_token_list	*token_get_node_index(t_token_list *token_list, int index)
{
	int				i;
	t_token_list	*aux;

	i = 0;
	aux = token_list;
	while (aux && i < index)
	{
		aux = aux->next;
		i++;
	}
	return (aux);
}
