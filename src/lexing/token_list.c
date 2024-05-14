/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:27:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/14 16:50:26 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_token_list	*token_create_node(char *lexeme, int token_type)
{
	t_token_list	*new_token;

	new_token = malloc(sizeof(t_token_list));
	new_token->token.lexeme = lexeme;
	new_token->token.type = token_type;
	new_token->next = NULL;
	return (new_token);
}

void	token_add_to_list(t_token_list **token_list, char *lexeme, \
		int token_type)
{
	t_token_list	*new_token;
	t_token_list	*last_node;

	new_token = token_create_node(lexeme, token_type);
	last_node = *token_list;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = new_token;
	else
		*token_list = new_token;
}

void	token_back_one_node(t_token_list *token_list, \
		t_token_list **node_to_back)
{
	t_token_list	*aux;

	aux = token_list;
	while (aux && aux->next != *node_to_back)
		aux = aux->next;
	*node_to_back = aux;
}

t_token_list	*token_get_sublist(t_token_list *token_list, int start, \
				int list_length)
{
	int				i;
	t_token_list	*aux;
	t_token_list	*new_token_list;

	i = 0;
	aux = token_list;
	new_token_list = NULL;
	while (aux && i < start)
	{
		aux = aux->next;
		i++;
	}
	i = 0;
	while (aux && i < list_length)
	{
		token_add_to_list(&new_token_list, ft_strdup(aux->token.lexeme), \
			aux->token.type);
		aux = aux->next;
		i++;
	}
	return (new_token_list);
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
