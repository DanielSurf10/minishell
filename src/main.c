/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:07 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/15 13:58:32 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

volatile int	g_signal;

int main(int argc, char *argv[], char *envp[])
{
	int				ret_code;
	char			*line;
	t_token_list	*token_list;
	t_exec_tree		*tree;
	t_minishell		data;

	tree = NULL;
	token_list = NULL;
	ret_code = 0;
	data = (t_minishell) {0};
	data.envp_list = env_create_list(envp);
	env_insert_node(&data.envp_list, "?", "0");
	g_signal = 0;
	init_signals();
	line = "ls -l";
	execution_signals(1);
	token_list = get_token_list(line);
	data.tree = get_tree(token_list, &data);
	token_clear_list(&token_list);

	if (g_signal == SIGINT)
		ret_code = 130;
	else
	{
		ret_code = exec_tree(data.tree, &data);
		if (data.tree == NULL)
			ft_putendl_fd("syntax error", STDERR_FILENO);
	}
	line = ft_itoa(ret_code);
	env_insert_node(&data.envp_list, "?", line);
	free(line);
	free_tree_all(&data.tree);
	env_clear_list(&data.envp_list);
	fd_list_close_clear(&data.fd_list);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (ret_code);
}
