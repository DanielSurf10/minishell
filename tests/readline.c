/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:43:13 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/23 19:31:56 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT || sig == SIGCONT || sig == SIGQUIT)
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
	char *line;

	signal(SIGINT, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGQUIT, signal_handler);
	line = readline("Escreva algo: ");

	while (line)
	{
		if (*line)
			add_history(line);
		printf("%s\n", line);
		free(line);
		line = readline("Escreva algo: ");
	}

	rl_clear_history();

	return (0);
}
