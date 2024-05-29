/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:07 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/29 20:01:41 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int main(void)
{
	int				ret_code;
	char			*line;
	t_token_list	*token_list;
	t_exec_tree		*tree;

	tree = NULL;
	token_list = NULL;
	ret_code = 0;
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	do
	{
		line = readline("minishell$ ");

		if (!line)
			break ;
		else if (!line[0])
			continue ;

		token_list = get_token_list(line);
		tree = get_tree(token_list);
		free(line);

		ret_code = exec_tree(tree);

		token_clear_list(&token_list);
		free_tree(&tree);

	} while (line);

	printf("\nret code main = %d\n", ret_code);
	rl_clear_history();

	return (0);
}
