/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:36:18 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/05 10:37:26 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*get_absolute_path(char *command, char **paths)
{
	int		i;
	int		full_path_len;
	char	*absolute_command;

	i = 0;
	absolute_command = NULL;
	while (paths[i])
	{
		full_path_len = ft_strlen(paths[i]) + ft_strlen(command) + 2;
		absolute_command = malloc(full_path_len);
		ft_strlcpy(absolute_command, paths[i], full_path_len);
		ft_strlcat(absolute_command, "/", full_path_len);
		ft_strlcat(absolute_command, command, full_path_len);
		if (access(absolute_command, F_OK | X_OK) == 0)
			break ;
		free(absolute_command);
		absolute_command = NULL;
		i++;
	}
	return (absolute_command);
}

char	*expand_command(char *command, t_envp_list *envp_list)
{
	int		i;
	int		full_path_len;
	char	*path_env;
	char	*absolute_command;
	char	**paths;

	i = 0;
	absolute_command = NULL;
	if (ft_strlen(command) > 0 && ft_strchr(command, '/') == NULL)
	{
		path_env = search_value(envp_list, "PATH");
		paths = ft_split(path_env, ':');
		free(path_env);
		absolute_command = get_absolute_path(command, paths);
		ft_free_split(paths);
	}
	if (!absolute_command)
		return (ft_strdup(command));
	return (absolute_command);
}
