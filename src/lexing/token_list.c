/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:27:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/15 08:43:05 by leobarbo         ###   ########.fr       */
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

void	token_add_to_list(t_token_list **tok_lst, char *lex, int token_type)
{
	t_token_list	*new_token;
	t_token_list	*last_node;

	new_token = token_create_node(lex, token_type);
	last_node = *tok_lst;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = new_token;
	else
		*tok_lst = new_token;
}

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

void	token_back_one_node(t_token_list *tok_lst, t_token_list **node_to_back)
{
	t_token_list	*aux;

	aux = tok_lst;
	while (aux && aux->next != *node_to_back)
		aux = aux->next;
	*node_to_back = aux;
}

t_token_list	*tok_get_sublst(t_token_list *tok_lst, int start, int lst_len)
{
	int				i;
	t_token_list	*aux;
	t_token_list	*new_token_list;

	i = 0;
	aux = tok_lst;
	new_token_list = NULL;
	while (aux && i < start)
	{
		aux = aux->next;
		i++;
	}
	i = 0;
	while (aux && i < lst_len)
	{
		token_add_to_list(&new_token_list, \
		ft_strdup(aux->token.lexeme), aux->token.type);
		aux = aux->next;
		i++;
	}
	return (new_token_list);
}
