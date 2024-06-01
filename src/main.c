/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:07 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/31 16:15:20 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

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
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	data.envp_list = store_to_list(envp);
	env_insert_node(&data.envp_list, "A", "\"");
	// env_insert_node(&data.envp_list, "PATH", "");

	line = readline("minishell$ ");
	while (line)
	{

		if (!line[0])
			continue ;

		token_list = get_token_list(line);
		data.tree = get_tree(token_list, &data);
		token_clear_list(&token_list);
		add_history(line);
		free(line);

		ret_code = exec_tree(data.tree, &data);

		free_tree(&data.tree);

		line = readline("minishell$ ");

	}

	env_clear_list(&data.envp_list);

	printf("\nret code main = %d\n", ret_code);
	rl_clear_history();

	return (0);
}
