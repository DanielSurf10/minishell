/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:25:24 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 15:21:29 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	token_get_state_50(char character)
{
	int	state;

	if (character == '\'')
		state = 51;
	else if (character == '\"')
		state = 52;
	else if (is_metacharacter(character) || character == '\0')
		state = 53;
	else if (!is_metacharacter(character))
		state = 50;
	else
		state = -1;
	return (state);
}

int	token_get_state_51(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\'')
		state = 50;
	else if (character != '\'')
		state = 51;
	else
		state = -1;
	return (state);
}

int	token_get_state_52(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\"')
		state = 50;
	else if (character != '\"')
		state = 52;
	else
		state = -1;
	return (state);
}
