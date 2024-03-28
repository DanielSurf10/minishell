/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:49:00 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/25 21:54:56 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_command_path(char *command, char **envp)
{
	// Expansão do caminho do comando
	return (ft_strjoin("/bin/", command));
}

void	set_input_and_output(t_command command)
{
	if (command.input != -1)
		dup2(command.input, STDIN_FILENO);
	if (command.output != -1)
		dup2(command.output, STDOUT_FILENO);
}

void	close_fds(t_command command)
{
	if (command.input != -1)
		close(command.input);
	if (command.output != -1)
		close(command.output);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	command_one;
	t_command	command_two;

	command_one.pid = fork();

	if (command_one.pid == 0)
	{
		// Nome do comando e o seu caminho
		command_one.command = ft_strdup("cat"); // Aqui faz o strdup para adaptar o código para dar free
		command_one.expanded_command = expand_command_path(command_one.command, envp);

		// Fd's de entrada e saída - se for -1 não é pra fazer o dup2
		command_one.input = open("infile", O_RDONLY);
		command_one.output = -1;

		// Argumentos
		command_one.arguments_count = 1;
		command_one.args = malloc((command_one.arguments_count + 1) * sizeof(char *));
		command_one.args[0] = ft_strdup(command_one.command);
		command_one.args[1] = ft_strdup("-e");
		command_one.args[2] = NULL;

		set_input_and_output(command_one);
		execve(command_one.expanded_command, command_one.args, envp);

		close_fds(command_one);

		free(command_one.command);
		free(command_one.expanded_command);
		ft_free_split(command_one.args);

		exit(1);
	}

	waitpid(command_one.pid, NULL, 0);

	return (0);
}
