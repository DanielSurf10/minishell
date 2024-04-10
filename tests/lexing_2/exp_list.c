/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:57:28 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/10 00:47:18 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_exp_list	*exp_create_node(t_token_list *token_lexeme, int token_type)
{
	t_exp_list	*new_token;

	new_token = malloc(sizeof(t_token_list));
	new_token->expression.token_list = token_lexeme;
	new_token->expression.type = token_type;
	new_token->next = NULL;
	return (new_token);
}

void	exp_add_to_list(t_exp_list **exp_list, t_token_list *token_lexeme, int token_type)
{
	t_exp_list	*new_token;
	t_exp_list	*last_node;

	new_token = exp_create_node(token_lexeme, token_type);
	last_node = *exp_list;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = new_token;
	else
		*exp_list = new_token;
}

void	exp_back_one_node(t_token_list *token_list, t_token_list **node_to_back)
{
	t_token_list	*aux;

	aux = token_list;
	while (aux && aux->next != *node_to_back)
		aux = aux->next;
	*node_to_back = aux;
}

t_token_list	*exp_get_first_n_nodes(t_token_list *token_list, int length)
{
	int				i;
	t_token_list	*aux;
	t_token_list	*new_token_list;

	i = 0;
	aux = token_list;
	new_token_list = NULL;
	while (aux && i < length)
	{
		token_add_to_list(&new_token_list, ft_strdup(aux->token.content), aux->token.type);
		aux = aux->next;
		i++;
	}
	return (new_token_list);
}

void	exp_clear_list(t_exp_list **exp_list)
{
	t_exp_list	*aux1;
	t_exp_list	*aux2;

	if (exp_list)
	{
		aux1 = *exp_list;
		while (aux1)
		{
			aux2 = aux1->next;
			token_clear_list(&aux1->expression.token_list);
			free(aux1);
			aux1 = aux2;
		}
		*exp_list = NULL;
	}
}
