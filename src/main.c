/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:07 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/23 22:00:49 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT || sig == SIGCONT)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_replace_line("", 0);
		}
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(void)
{
	char	*line;
	char	**split_line;

	signal(SIGINT, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

	line = readline("minishell$");
	split_line = ft_split(line, ' ');

	// exec_commands(split_line);

	free(line);
	ft_free_split(split_line);
	rl_clear_history();

	return (0);
}
