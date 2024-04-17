/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:00:46 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/17 00:18:30 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	cmd_get_state_1(t_token_list *node)
{
	int	state;

	if (node == NULL)
		state = 1;
	else if (node->token.type == PIPE)
		state = 20;
	else if (node->token.type != PIPE)
		state = 30;
	else
		state = -1;
	return (state);
}

int	cmd_get_state_30(t_token_list *node)
{
	int	state;

	if (node == NULL || node->token.type == PIPE)
		state = 31;
	else if (node->token.type != PIPE)
		state = 30;
	else
		state = -1;
	return (state);
}
