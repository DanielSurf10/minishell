/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:50:35 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/17 00:00:30 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	cmd_state_is_final(int state)
{
	if (state == 20
		|| state == 31)
		return (1);
	return (0);
}

int	cmd_state_requires_backtrack(int state)
{
	if (state == 31)
		return (1);
	return (0);
}

int	cmd_get_token_type(int state)
{
	int	type;

	if (state == 20)
		type = PIPE;
	else if (state == 31)
		type = COMMAND;
	else
		type = -1;
	return (type);
}

int	cmd_get_next_state(int state, t_token_list *node)
{
	int	new_state;

	if (state == 1)
		new_state = cmd_get_state_1(node);
	else if (state == 30)
		new_state = cmd_get_state_30(node);
	else
		new_state = -1;
	return (new_state);
}
