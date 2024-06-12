/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree_cmd_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:04:15 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/11 21:08:16 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	make_subshell_or_command(t_token_list *args, t_exec_tree **tree, \
			t_minishell *data)
{
	if (args && args->token.type == OPEN_PARENTHESIS)
	{
		if (index_to_close_parenthesis(args->next) != token_list_size(args) - 1)
			free_tree(tree);
		else
		{
			(*tree)->type = SUBSHELL;
			(*tree)->command = token_get_sublist(args, 1, \
				token_list_size(args) - 2);
			(*tree)->subshell = get_tree((*tree)->command, data);
			token_clear_list(&(*tree)->command);
			if (!(*tree)->subshell)
				free_tree(&(*tree));
		}
	}
	else
	{
		(*tree)->type = COMMAND;
		(*tree)->command = token_get_sublist(args, 0, token_list_size(args));
	}
}

static void	make_redirects(t_exec_tree **tree, t_token_list *redir_list, \
			t_minishell *data, t_token_list *args)
{
	char	*str;

	(*tree)->type = redir_list->token.type;
	(*tree)->left = malloc(sizeof(t_exec_tree));
	ft_bzero((*tree)->left, sizeof(t_exec_tree));
	(*tree)->left->type = COMMAND;
	if ((*tree)->type == REDIRECT_HEREDOC)
	{
		str = create_here_doc(redir_list->next->token.lexeme, data);
		(*tree)->left->command = get_token_list(str);
		free(str);
	}
	else
		(*tree)->left->command = token_get_sublist(redir_list, 1, 1);
	if ((*tree)->left->command)
		(*tree)->right = make_tree_cmd_recursive(\
			token_get_node_index(redir_list, 2), args, data);
	if (!(*tree)->right || !(*tree)->left->command)
		free_tree(&(*tree));
}

t_exec_tree	*make_tree_cmd_recursive(t_token_list *redir_list, \
			t_token_list *args, t_minishell *data)
{
	t_exec_tree		*tree;

	tree = malloc(sizeof(t_exec_tree));
	ft_bzero(tree, sizeof(t_exec_tree));
	if (!redir_list)
	{
		if (args && args->token.type == OPEN_PARENTHESIS)
			make_subshell_or_command(args, &tree, data);
		else
		{
			tree->type = COMMAND;
			tree->command = token_get_sublist(args, 0, token_list_size(args));
		}
	}
	else if (redir_list && redir_list->token.type != WORD && redir_list->next
		&& redir_list->next->token.type == WORD)
		make_redirects(&tree, redir_list, data, args);
	else
		free_tree(&tree);
	return (tree);
}
