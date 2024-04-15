/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:00:51 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/14 21:30:49 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_cmd_list	*token_get_sublist(t_token_list *token_list, int start, int list_length)		// Essa função eu quero por junto num arquivo de manipulação de t_token_list
{
	int				i;
	t_token_list	*aux;
	t_token_list	*new_token_list;

	i = 0;
	aux = token_list;
	new_token_list = NULL;
	while (aux && i < start)		// Essa primeira parte chega até o primeiro nó
	{
		aux = aux->next;
		i++;
	}
	while (aux && i < list_length)	// Essa parte copia os nós para uma outra lista até um certo nó
	{
		token_add_to_list(&new_token_list, ft_strdup(aux->token.lexeme), aux->token.type);
		aux = aux->next;
		i++;
	}
	return (new_token_list);
}

t_token_list	*cmd_get_cmd_tokens(t_token_list *token_list, int length)		// Aqui dá pra chamar de algo token_sublist ou sla
{
	int				i;
	t_token_list	*aux;
	t_token_list	*new_token_list;

	i = 0;
	aux = token_list;
	new_token_list = NULL;
	while (aux && i < length)
	{
		token_add_to_list(&new_token_list, ft_strdup(aux->token.lexeme), aux->token.type);
		aux = aux->next;
		i++;
	}
	return (new_token_list);
}

/**
 * @brief Get the cmd list object
 *
 * @param full_token_list	- Lista de tokens completa
 * @param start				- Posição inicial da lista
 * @param list_length		- Qual o tamanho da lista de tokens que eu quero considerar
 * @return t_cmd_list*
 */
t_cmd_list	*get_cmd_list(t_token_list *full_token_list, int start, int list_length)
{
	int				i;
	int				state;
	int				length;
	int				token_type;
	t_token_list	*aux;
	t_token_list	*token_list;
	t_token_list	*token_lexeme;
	t_token_list	*first_node_token;
	t_cmd_list		*cmd_list;

	if (!full_token_list)
		return (NULL);
	i = 0;
	length = 0;
	token_list = token_get_sublist(full_token_list, start, list_length);
	aux = token_list;
	first_node_token = token_list;
	cmd_list = NULL;
	while (i <= list_length)
	{
		state = cmd_get_next_state(state, aux);
		length += 1;

		if (cmd_state_is_final(state))
		{
			if (cmd_state_requires_backtrack(state))
			{
				cmd_back_one_node(token_list, &aux);
				length -= 1;
				i--;
			}
			token_type = cmd_get_token_type(state);
			if (token_type == COMMAND)
				token_lexeme = cmd_get_cmd_tokens(first_node_token, length);
			else
				token_lexeme = NULL;
			cmd_add_to_list(&cmd_list, token_lexeme, token_type);
			first_node_token = aux->next;
			length = 0;
			state = 1;
		}
		i++;
		if (aux)
			aux = aux->next;
	}

	token_clear_list(token_list);
	return (cmd_list);
}
