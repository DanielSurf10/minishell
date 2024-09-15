/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:03:18 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 15:25:18 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	token_state_is_final(int state)
{
	if (state == 20
		|| state == 31 || state == 32
		|| state == 41 || state == 42
		|| state == 53)
		return (1);
	return (0);
}

int	token_state_requires_backtrack(int state)
{
	if (state == 32
		|| state == 42
		|| state == 53)
		return (1);
	return (0);
}

int	token_get_next_state(int state, char character)
{
	int	new_state;

	if (state == 1)
		new_state = token_get_state_1(character);
	else if (state == 30)
		new_state = token_get_state_30(character);
	else if (state == 40)
		new_state = token_get_state_40(character);
	else if (state == 50)
		new_state = token_get_state_50(character);
	else if (state == 51)
		new_state = token_get_state_51(character);
	else if (state == 52)
		new_state = token_get_state_52(character);
	else
		new_state = -1;
	return (new_state);
}

int	token_get_token_type(int state)
{
	int	type;

	if (state == 20)
		type = PIPE;
	else if (state == 31)
		type = REDIRECT_OUTPUT_APPEND;
	else if (state == 32)
		type = REDIRECT_OUTPUT;
	else if (state == 41)
		type = REDIRECT_HEREDOC;
	else if (state == 42)
		type = REDIRECT_INPUT;
	else if (state == 53)
		type = WORD;
	else
		type = -1;
	return (type);
}
