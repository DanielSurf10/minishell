/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:25:24 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/30 20:49:27 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	get_state_80(char character)
{
	int	state;

	if (character == '\'')
		state = 81;
	else if (character == '\"')
		state = 82;
	else if (is_metacharacter(character) == 1 || character == '\0')
		state = 83;
	else if (is_metacharacter(character) == 0)
		state = 80;
	else
		state = -1;
	return (state);
}

int	get_state_81(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\'')
		state = 80;
	else if (character != '\'')
		state = 81;
	else
		state = -1;
	return (state);
}

int	get_state_82(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\"')
		state = 80;
	else if (character != '\"')
		state = 82;
	else
		state = -1;
	return (state);
}