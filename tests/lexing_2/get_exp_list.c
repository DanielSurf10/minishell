/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:23:44 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/10 01:33:52 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	exp_list_size(t_token_list *token_list)
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

t_exp_list	*get_exp_list(t_token_list *token_list)
{
	int				i;
	int				state;
	int				length;
	int				token_type;
	int				token_list_size;
	t_token_list	*aux;
	t_token_list	*first_node_token;
	t_token_list	*token_lexeme;
	t_exp_list		*exp_list;

	if (!token_list)
		return (NULL);
	i = 0;
	state = 1;
	length = 0;
	token_list_size = exp_list_size(token_list);
	aux = token_list;
	first_node_token = token_list;
	exp_list = NULL;
	while (i <= token_list_size)
	{
		state = exp_get_next_state(state, aux);
		length += 1;

		if (exp_state_is_final(state))
		{
			if (exp_state_requires_backtrack(state))
			{
				exp_back_one_node(token_list, &aux);
				length -= 1;
				i--;
			}
			token_type = exp_get_token_type(state);
			token_lexeme = exp_get_first_n_nodes(first_node_token, length);
			exp_add_to_list(&exp_list, token_lexeme, token_type);
			first_node_token = aux->next;
			length = 0;
			state = 1;
		}
		i++;
		if (aux)
			aux = aux->next;
	}
	return (exp_list);
}
