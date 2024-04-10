/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:49:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/10 01:00:00 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_an_expression(t_token_list *node)
{
	if (node->token.type == WORD
		|| node->token.type == PIPE
		|| node->token.type == REDIRECT_INPUT
		|| node->token.type == REDIRECT_HEREDOC
		|| node->token.type == REDIRECT_OUTPUT
		|| node->token.type == REDIRECT_OUTPUT_APPEND)
		return (1);
	return (0);
}
