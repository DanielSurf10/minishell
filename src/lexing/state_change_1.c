/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:25:24 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 15:20:26 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	token_get_state_1(char character)
{
	int	state;

	if (character == '|')
		state = 20;
	else if (character == '<')
		state = 40;
	else if (character == '>')
		state = 30;
	else if (character == '\'')
		state = 51;
	else if (character == '\"')
		state = 52;
	else if (character == '\0' || ft_isspace(character))
		state = 1;
	else if (!is_metacharacter(character))
		state = 50;
	else
		state = -1;
	return (state);
}

int	token_get_state_30(char character)
{
	int	state;

	if (character == '>')
		state = 31;
	else if (character != '>')
		state = 32;
	else
		state = -1;
	return (state);
}

int	token_get_state_40(char character)
{
	int	state;

	if (character == '<')
		state = 41;
	else if (character != '<')
		state = 42;
	else
		state = -1;
	return (state);
}
