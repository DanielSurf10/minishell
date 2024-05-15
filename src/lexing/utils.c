/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:42:42 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/15 08:39:08 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

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

int	token_list_size(t_token_list *token_list)
{
	int				i;
	t_token_list	*aux;

	i = 0;
	aux = token_list;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}
