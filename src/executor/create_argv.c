/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:53:20 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/18 11:07:54 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_token_list	*get_expanded_list(t_token_list *token_list, t_envp_list *envp)
{
	char			*expanded_string;
	t_token_list	*aux;
	t_token_list	*expanded_list;

	aux = token_list;
	expanded_list = NULL;
	while (aux)
	{
		expanded_string = expand_string(aux->token.lexeme, envp);
		if (ft_strlen(expanded_string) != 0)
			token_add_to_list(&expanded_list, ft_strdup(expanded_string), WORD);
		free(expanded_string);
		aux = aux->next;
	}
	return (expanded_list);
}

char	**create_argv(t_exec_tree *tree, t_minishell *data)
{
	int				i;
	int				args_num;
	char			**argv;
	t_token_list	*expanded_list;

	i = 0;
	expanded_list = get_expanded_list(tree->command, data->envp_list);
	args_num = token_list_size(expanded_list);
	argv = malloc((args_num + 1) * sizeof(char *));
	argv[args_num] = NULL;
	while (i < args_num)
	{
		argv[i] = expand_string(token_get_node_index(\
			expanded_list, i)->token.lexeme, data->envp_list);
		i++;
	}
	token_clear_list(&expanded_list);
	return (argv);
}
