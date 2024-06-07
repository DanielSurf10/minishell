/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:07 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/07 18:26:45 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

volatile int	g_signal;

static void	print_m(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
}

void	print_menu(void)
{
	print_m(ORANGE"═══════════════════════════");
	print_m(ORANGE"════════════════════════════════════════\n");
	print_m(BLUE"░░░╗   ░░░╗░░╗░░░╗   ░░╗░░╗");
	print_m(BLUE"░░░░░░░╗░░╗  ░░╗░░░░░░░╗░░╗     ░░╗     \n");
	print_m(BLUE"░░░░╗ ░░░░║░░║░░░░╗  ░░║░░║");
	print_m(BLUE"░░╔════╝░░║  ░░║░░╔════╝░░║     ░░║     \n");
	print_m(BLUE"░░╔░░░░╔░░║░░║░░╔░░╗ ░░║░░║");
	print_m(BLUE"░░░░░░░╗░░░░░░░║░░░░░╗  ░░║     ░░║     \n");
	print_m(BLUE"░░║╚░░╔╝░░║░░║░░║╚░░╗░░║░░║");
	print_m(BLUE"╚════░░║░░╔══░░║░░╔══╝  ░░║     ░░║     \n");
	print_m(BLUE"░░║ ╚═╝ ░░║░░║░░║ ╚░░░░║░░║");
	print_m(BLUE"░░░░░░░║░░║  ░░║░░░░░░░╗░░░░░░░╗░░░░░░░╗\n");
	print_m(BLUE"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝");
	print_m(BLUE"╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	print_m(ORANGE"═══════════════════════════");
	print_m(ORANGE"════════════════════════════════════════\n");
	print_m(RST);
}

char	*get_line_to_readline(t_envp_list *env_list)
{
	int			i;
	int			length;
	char		*line;
	const char	*vars[2] = {search_value(env_list, "USER"), \
							search_value(env_list, "PWD")};
	const char	*to_print[] = {ORANGE, vars[0], RST, "\001🥲 \002", CYAN, vars[1], RST, \
								": ", NULL};

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
	free((char *)vars[0]);
	free((char *)vars[1]);
	return (line);
}

int main(int argc, char *argv[], char *envp[])
{
	int				ret_code;
	int				backup_fd_in;
	char			*line;
	char			*line_to_readline;
	t_token_list	*token_list;
	t_exec_tree		*tree;
	t_minishell		data;
	t_termios		term;

	tree = NULL;
	token_list = NULL;
	ret_code = 0;
	print_menu();
	backup_fd_in = dup(STDIN_FILENO);
	ft_memset(&data, 0, sizeof(data));
	fd_list_add_fd(&data.fd_list, backup_fd_in);
	data.envp_list = env_create_list(envp);
	env_insert_node(&data.envp_list, "?", "0");
	tcgetattr(STDIN_FILENO, &term);
	while (g_signal != -1)
	{
		g_signal = 0;
		init_signals();
		dup2(backup_fd_in, STDIN_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		line_to_readline = get_line_to_readline(data.envp_list);
		line = readline(line_to_readline);
		free(line_to_readline);
		execution_signals(1);
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
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
	}
	env_clear_list(&data.envp_list);
	fd_list_close_clear(&data.fd_list);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (ret_code);
}
