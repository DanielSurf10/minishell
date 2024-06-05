/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:07 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/05 14:11:26 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

int	g_signal;

// void	signal_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

char	*get_line_to_readline(t_envp_list *env_list)
{
	int			i;
	int			length;
	char		*line;
	const char	*vars[3] = {search_value(env_list, "USER"), \
							search_value(env_list, "PWD")};
	const char	*to_print[] = {ORANGE, vars[0], RST, "@", CYAN, vars[1], RST, \
								": ", "\001", NULL};

	i = 0;
	length = 0;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	free((char*)vars[0]);
	free((char*)vars[1]);
	return (line);
}

int main(int argc, char *argv[], char *envp[])
{
	int				ret_code;
	char			*line;
	char			*line_to_readline;
	t_token_list	*token_list;
	t_exec_tree		*tree;
	t_minishell		data;
	t_termios		term;

	tree = NULL;
	token_list = NULL;
	ret_code = 0;
	g_signal = 0;

	// signal(SIGINT, signal_handler);
	// signal(SIGTSTP, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGPIPE, SIG_IGN);
	init_signals();

	ft_memset(&data, 0, sizeof(data));
	data.envp_list = env_create_list(envp);
	env_insert_node(&data.envp_list, "?", "0");
	// env_insert_node(&data.envp_list, "A", "\"");
	// env_insert_node(&data.envp_list, "file", "todo");
	// env_insert_node(&data.envp_list, "PATH", "");

	tcgetattr(STDIN_FILENO, &term);
	while (data.is_heredoc == 0)
	{
		// line_to_readline = get_line_to_readline(data.envp_list);
		// line = readline(line_to_readline);
		// free(line_to_readline);
		if (isatty(STDIN_FILENO))
		{
			line_to_readline = get_line_to_readline(data.envp_list);
			line = readline(line_to_readline);
			free(line_to_readline);
		}
		else
		{
			line = readline(NULL);
		}

		if (!line)
			break ;
		else if (!line[0])
		{
			free(line);
			continue ;
		}

		token_list = get_token_list(line);
		data.tree = get_tree(token_list, &data);
		token_clear_list(&token_list);
		add_history(line);
		free(line);

		if (data.is_heredoc == 0)
		{
			ret_code = exec_tree(data.tree, &data);

			if (data.tree == NULL)
				ft_putendl_fd("syntax error", STDERR_FILENO);

			line = ft_itoa(ret_code);
			env_insert_node(&data.envp_list, "?", line);
			free(line);
			free_tree_all(&data.tree);
		}

		init_signals();
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}

	env_clear_list(&data.envp_list);

	rl_clear_history();

	if (data.is_heredoc == 0)
	{
		// printf("\nret code main = %d\n", ret_code);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}

	return (ret_code);
}
