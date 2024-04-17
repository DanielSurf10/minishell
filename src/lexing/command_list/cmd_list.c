/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:05:16 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/17 00:29:32 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_cmd_list	*cmd_create_node(t_token_list *token_lexeme, int token_type)
{
	t_cmd_list	*new_token;

	new_token = malloc(sizeof(t_cmd_list));
	new_token->command.token_list = token_lexeme;
	new_token->command.type = token_type;
	new_token->next = NULL;
	return (new_token);
}

void	cmd_add_to_list(t_cmd_list **cmd_list, t_token_list *token_lexeme, int token_type)
{
	t_cmd_list	*new_token;
	t_cmd_list	*last_node;

	new_token = cmd_create_node(token_lexeme, token_type);
	last_node = *cmd_list;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = new_token;
	else
		*cmd_list = new_token;
}

void	cmd_clear_list(t_cmd_list **cmd_list)
{
	t_cmd_list	*aux1;
	t_cmd_list	*aux2;

	if (cmd_list)
	{
		aux1 = *cmd_list;
		while (aux1)
		{
			aux2 = aux1->next;
			if (aux1->command.token_list)
				token_clear_list(&aux1->command.token_list);
			free(aux1);
			aux1 = aux2;
		}
		*cmd_list = NULL;
	}
}
