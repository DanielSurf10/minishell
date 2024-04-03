/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:01:34 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/02 21:01:51 by danbarbo         ###   ########.fr       */
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

	i = 0;
	state = 1;
	lexeme_length = 0;
	str_length = ft_strlen(str);
	token_list = NULL;
	while (i <= str_length)		// Aqui o '\0' tem que ser considerado também
	{
		state = get_next_state(state, str[i]);
		if (state != 1)
			lexeme_length += 1;

		if (state == -1)
		{
			clear_token_list(&token_list);
			break ;
		}

		if (state_is_final(state))
		{
			if (state_requires_backtrack_one_char(state))
			{
				i -= 1;
				lexeme_length -= 1;
			}
			token_type = get_token_type(state);
			lexeme = ft_substr(str, i - (lexeme_length - 1), lexeme_length);
			add_token_to_list(&token_list, lexeme, token_type);
			lexeme_length = 0;
			state = 1;
		}
		i++;
	}
	return (token_list);
}
