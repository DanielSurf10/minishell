/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:03:52 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/11 20:37:23 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_values(t_aux_tree *aux_tree, t_token_list *token_list)
{
	ft_bzero(aux_tree, sizeof(t_aux_tree));
	aux_tree->aux = token_list;
}

static void	tree_inside_parentesis(t_aux_tree *aux_tree)
{
	aux_tree->idx_parenthesis = index_to_close_parenthesis(aux_tree->aux->next);
	if (aux_tree->idx_parenthesis != -1)
	{
		aux_tree->aux2 = token_get_sublist(aux_tree->aux, 0, \
			aux_tree->idx_parenthesis + 1);
		token_join_lists(&aux_tree->args, aux_tree->aux2);
		token_clear_list(&aux_tree->aux2);
		aux_tree->aux = token_get_node_index(aux_tree->aux, \
			aux_tree->idx_parenthesis);
	}
	else
		aux_tree->aux = NULL;
}

static void	put_redirect_on_list(t_aux_tree *aux_tree)
{
	token_add_to_list(&aux_tree->redir_list, NULL, aux_tree->aux->token.type);
	if (aux_tree->aux->next)
	{
		token_add_to_list(&aux_tree->redir_list, \
			ft_strdup(aux_tree->aux->next->token.lexeme), \
			aux_tree->aux->next->token.type);
		aux_tree->aux = aux_tree->aux->next;
	}
}

t_exec_tree	*make_tree_cmd(t_token_list *token_list, t_minishell *data)
{
	t_aux_tree	aux_tree;

	init_values(&aux_tree, token_list);
	while (aux_tree.aux)
	{
		if (aux_tree.aux->token.type == OPEN_PARENTHESIS)
			tree_inside_parentesis(&aux_tree);
		else if (aux_tree.aux->token.type >= REDIRECT_INPUT
			&& aux_tree.aux->token.type <= REDIRECT_OUTPUT_APPEND)
			put_redirect_on_list(&aux_tree);
		else if (aux_tree.aux->token.type != CLOSE_PARENTHESIS)
			token_add_to_list(&aux_tree.args, \
				ft_strdup(aux_tree.aux->token.lexeme), \
				aux_tree.aux->token.type);
		if (aux_tree.aux)
			aux_tree.aux = aux_tree.aux->next;
	}
	if (aux_tree.idx_parenthesis != -1)
		aux_tree.tree = make_tree_cmd_recursive(aux_tree.redir_list, \
							aux_tree.args, data);
	token_clear_list(&aux_tree.args);
	token_clear_list(&aux_tree.redir_list);
	return (aux_tree.tree);
}
