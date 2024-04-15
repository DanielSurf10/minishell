/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:27:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/15 17:50:22 by danbarbo         ###   ########.fr       */
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

void	token_add_to_list(t_token_list **token_list, char *lexeme, int token_type)
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

void	token_back_one_node(t_token_list *token_list, t_token_list **node_to_back)
{
	t_token_list	*aux;

	aux = token_list;
	while (aux && aux->next != *node_to_back)
		aux = aux->next;
	*node_to_back = aux;
}

t_token_list	*token_get_sublist(t_token_list *token_list, int start, int list_length)
{
	int				i;
	t_token_list	*aux;
	t_token_list	*new_token_list;

	i = 0;
	aux = token_list;
	new_token_list = NULL;
	while (aux && i < start)		// Essa primeira parte chega até o primeiro nó
	{									// Até o indice do start
		aux = aux->next;
		i++;						// Aqui o i conta até chegar no start
	}
	i = 0;
	while (aux && i < list_length)	// Essa parte copia os nós para uma outra lista até um certo nó
	{									// Até a lista ter o tamanho list_length
		token_add_to_list(&new_token_list, ft_strdup(aux->token.lexeme), aux->token.type);
		aux = aux->next;
		i++;						// Aqui o i conta até chegar no tamanho máximo
	}
	return (new_token_list);
}

// t_token_list	*cmd_get_cmd_tokens(t_token_list *token_list, int length)		// Aqui dá pra chamar de algo token_sublist ou sla
// {
// 	int				i;
// 	t_token_list	*aux;
// 	t_token_list	*new_token_list;
//
// 	i = 0;
// 	aux = token_list;
// 	new_token_list = NULL;
// 	while (aux && i < length)
// 	{
// 		token_add_to_list(&new_token_list, ft_strdup(aux->token.lexeme), aux->token.type);
// 		aux = aux->next;
// 		i++;
// 	}
// 	return (new_token_list);
// }
