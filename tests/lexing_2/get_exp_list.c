/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:23:44 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/08 23:25:21 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_exp_list	*get_exp_list(t_token_list *token_list)
{
	int				state;
	int				length;
	int				token_type;
	t_token_list	*aux;
	t_token_list	*token_lexeme;
	t_exp_list		*exp_list;

	if (!token_list)
		return (NULL);
	state = 1;
	length = 0;
	aux = token_list;
	exp_list = NULL;
	while (aux)
	{
		state = exp_get_next_state(state, aux);

		length += 1;

		if (exp_state_is_final(state))
		{
			if (exp_state_requires_backtrack(state))
			{
				exp_back_one_node(token_list, &aux);
				length -= 1;
			}
			token_type = exp_get_token_type(state);
			token_lexeme = exp_get_first_n_nodes(aux, length);
			exp_add_to_list(&exp_list, token_lexeme, token_type);
			length = 0;
			state = 1;
		}
		aux = aux->next;
	}
	return (exp_list);
}
