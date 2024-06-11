/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:03:52 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/11 19:04:08 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_exec_tree	*make_tree_cmd(t_token_list *token_list, t_minishell *data)
{
	int				redir_counter;
	int				idx_parenthesis;
	t_token_list	*aux;
	t_token_list	*aux2;
	t_token_list	*args;
	t_token_list	*redir_list;
	t_exec_tree		*tree;

	redir_counter = 0;
	aux = token_list;
	args = NULL;
	redir_list = NULL;
	tree = NULL;
	idx_parenthesis = 0;
	while (aux)
	{
		if (aux->token.type == OPEN_PARENTHESIS)
		{
			idx_parenthesis = index_to_close_parenthesis(aux->next);
			if (idx_parenthesis != -1)
			{
				aux2 = token_get_sublist(aux, 0, idx_parenthesis + 1);
				token_join_lists(&args, aux2);
				token_clear_list(&aux2);
				aux = token_get_node_index(aux, idx_parenthesis);
			}
			else
				break ;
		}
		else if (aux->token.type >= REDIRECT_INPUT && aux->token.type <= REDIRECT_OUTPUT_APPEND)
		{
			token_add_to_list(&redir_list, NULL, aux->token.type);
			if (aux->next)
			{
				token_add_to_list(&redir_list, ft_strdup(aux->next->token.lexeme), aux->next->token.type);
				aux = aux->next;
			}
		}
		else if (aux->token.type != CLOSE_PARENTHESIS)
			token_add_to_list(&args, ft_strdup(aux->token.lexeme), aux->token.type);
		if (aux)
			aux = aux->next;
	}
	if (idx_parenthesis == -1)
	{
		token_clear_list(&args);
		token_clear_list(&redir_list);
		return (NULL);
	}

	tree = make_tree_cmd_recursive(redir_list, args, data);

	token_clear_list(&args);
	token_clear_list(&redir_list);

	return (tree);
}
