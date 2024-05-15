/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:01:34 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/15 13:10:33 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	aux_token_state_final(t_aux_token_list *aux, char *str, \
		t_token_list **token_list)
{
	if (token_state_requires_backtrack(aux->state))
	{
		aux->i -= 1;
		aux->lexeme_length -= 1;
	}
	aux->token_type = token_get_token_type(aux->state);
	if (aux->token_type == WORD)
		aux->lexeme = ft_substr(str, aux->i - (aux->lexeme_length - 1), \
		aux->lexeme_length);
	else
		aux->lexeme = NULL;
	token_add_to_list(token_list, aux->lexeme, aux->token_type);
	aux->lexeme_length = 0;
	aux->state = 1;
}

t_token_list	*get_token_list(char *str)
{
	t_token_list		*token_list;
	t_aux_token_list	aux;

	if (!str)
		return (NULL);
	ft_bzero(&aux, sizeof(t_aux_token_list));
	aux.state = 1;
	aux.str_length = ft_strlen(str);
	token_list = NULL;
	while (aux.i <= aux.str_length)
	{
		aux.state = token_get_next_state(aux.state, str[aux.i]);
		if (aux.state != 1)
			aux.lexeme_length += 1;
		if (aux.state == -1)
		{
			token_clear_list(&token_list);
			break ;
		}
		if (token_state_is_final(aux.state))
			aux_token_state_final(&aux, str, &token_list);
		aux.i++;
	}
	return (token_list);
}
