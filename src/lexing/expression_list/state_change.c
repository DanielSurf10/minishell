/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:48:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/17 00:12:42 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	exp_get_state_1(t_token_list *node)
{
	int	state;

	if (node == NULL)
		state = 1;
	else if (node->token.type == OPEN_PARENTHESIS)
		state = 20;
	else if (node->token.type == CLOSE_PARENTHESIS)
		state = 30;
	else if (node->token.type == AND)
		state = 40;
	else if (node->token.type == OR)
		state = 50;
	else if (is_an_command_element(node))
		state = 60;
	else
		state = -1;
	return (state);
}

int	exp_get_state_60(t_token_list *node)
{
	int	state;

	if (node == NULL || is_an_command_element(node) == 0)
		state = 61;
	else if (is_an_command_element(node))
		state = 60;
	else
		state = -1;
	return (state);
}
