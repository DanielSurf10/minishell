/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:42:42 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/29 19:33:49 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metacharacter(char character)
{
	if (character == '('
		|| character == ')'
		|| character == '|'
		|| character == '&'
		|| character == '<'
		|| character == '>'
		|| character == '\''
		|| character == '\"'
		|| ft_isspace(character))
		return (1);
	return (0);
}

int	is_an_command_element(t_token_list *node)
{
	if (node && (node->token.type == WORD
			|| node->token.type == PIPE
			|| node->token.type == REDIRECT_INPUT
			|| node->token.type == REDIRECT_HEREDOC
			|| node->token.type == REDIRECT_OUTPUT
			|| node->token.type == REDIRECT_OUTPUT_APPEND))
		return (1);
	return (0);
}
