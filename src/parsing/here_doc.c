/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:31:03 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/04 18:23:53 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_error_message(char *delimiter)
{
	int			length;
	char		*message_to_print;
	const char	*message = "Expecting delimiter (required '";

	length = ft_strlen(message) + ft_strlen(delimiter) + 3;
	message_to_print = malloc(length);
	ft_strlcpy(message_to_print, message, length);
	ft_strlcat(message_to_print, delimiter, length);
	ft_strlcat(message_to_print, "')", length);
	ft_putendl_fd(message_to_print, STDERR_FILENO);
	free(message_to_print);
}

void	write_on_file(int fd, char *line, int need_to_expand, \
						t_envp_list *envp_list)
{
	char	*expanded_line;

	if (need_to_expand)
	{
		expanded_line = expand_string_heredoc(line, envp_list);
		ft_putendl_fd(expanded_line, fd);
		free(expanded_line);
	}
	else
		ft_putendl_fd(line, fd);
}

void	here_doc_fork(char *file_name, char *delimiter, t_envp_list *envp_list)
{
	int		fd;
	int		need_to_expand;
	char	*line;
	char	*expanded_line;
	char	*delimiter_without_quotes;

	need_to_expand = !(ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'));
	delimiter_without_quotes = remove_quotes(delimiter);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter_without_quotes, -1) == 0)
		{
			if (!line)
				print_error_message(delimiter);
			break ;
		}
		write_on_file(fd, line, need_to_expand, envp_list);
		free(line);
	}
	free(delimiter_without_quotes);
	close(fd);
}

char	*create_here_doc_name(char *delimiter)
{
	int				length;
	char			*prefix;
	char			*file_name;
	const char		*path = "/tmp/";
	unsigned long	num;

	num = (unsigned long) delimiter;
	prefix = ft_itoa((int) num);
	length = ft_strlen(path) + ft_strlen(prefix) + ft_strlen(delimiter) + 1;
	file_name = malloc(length);
	ft_strlcpy(file_name, path, length);
	ft_strlcat(file_name, prefix, length);
	ft_strlcat(file_name, delimiter, length);
	free(prefix);
	return (file_name);
}

char	*create_here_doc(char *delimiter, t_minishell *data)
{
	int		pid;
	char	*file_name;

	file_name = create_here_doc_name(delimiter);
	pid = fork();
	if (pid == 0)
	{
		data->is_heredoc = 1;
		here_doc_fork(file_name, delimiter, data->envp_list);
		free(file_name);
		return (NULL);
	}
	wait(NULL);
	return (file_name);
}

// Fork para fazer o heredoc
// fork()

// pai
// wait()

// filho
// executar heredoc
	// criar arquivo do heredoc
	// apagar tudo do data
	// obs: apagar arquivo quando for apagar a árvore
