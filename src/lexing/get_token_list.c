/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:01:34 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/14 16:52:35 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token_list	*get_token_list(char *str)
{
	int				i;
	int				state;
	int				token_type;
	int				str_length;
	int				lexeme_length;
	char			*lexeme;
	t_token_list	*token_list;

	if (!str)
		return (NULL);
	i = 0;
	state = 1;
	lexeme_length = 0;
	str_length = ft_strlen(str);
	token_list = NULL;
	while (i <= str_length)		// Aqui o '\0' tem que ser considerado também
	{
		state = token_get_next_state(state, str[i]);

		if (state != 1)
			lexeme_length += 1;

		if (state == -1)
		{
			token_clear_list(&token_list);
			break ;
		}

		if (token_state_is_final(state))
		{
			if (token_state_requires_backtrack(state))
			{
				i -= 1;
				lexeme_length -= 1;
			}
			token_type = token_get_token_type(state);

			if (token_type == WORD)
				lexeme = ft_substr(str, i - (lexeme_length - 1), lexeme_length);
			else
				lexeme = NULL;
			token_add_to_list(&token_list, lexeme, token_type);
			lexeme_length = 0;
			state = 1;
		}
		i++;
	}
	return (token_list);
}
