/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:49:32 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/08 23:38:46 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	exp_state_is_final(int state)
{
	if (state == 20
		|| state == 30
		|| state == 40
		|| state == 50
		|| state == 61)
		return (1);
	return (0);
}

int	exp_state_requires_backtrack(int state)
{
	if (state == 61)
		return (1);
	return (0);
}

int	exp_get_next_state(int state, t_token_list *node)
{
	int	new_state;

	if (state == 1)
		new_state = exp_get_state_1(node);
	else if (state == 60)
		new_state = exp_get_state_60(node);
	else
		new_state = -1;
	return (new_state);
}

int	exp_get_token_type(int state)
{
	int	type;

	if (state == 20)
		type = OPEN_PARENTHESIS;
	else if (state == 30)
		type = CLOSE_PARENTHESIS;
	else if (state == 40)
		type = AND;
	else if (state == 50)
		type = OR;
	else if (state == 61)
		type = EXPRESSION;
	else
		type = -1;
	return (type);
}
