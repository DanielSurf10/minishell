/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:34:16 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/09 16:18:19 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static void	cd_print_error_message(char *folder)
{
	int			length;
	char		*message_to_print;
	const char	*message[2] = {RED"ERROR: "RST"cd: '", \
								"': file or directory does not exist"};

	length = ft_strlen(message[0]) + ft_strlen(folder) \
						+ ft_strlen(message[1]) + 1;
	message_to_print = malloc(length);
	ft_strlcpy(message_to_print, message[0], length);
	ft_strlcat(message_to_print, folder, length);
	ft_strlcat(message_to_print, message[1], length);
	ft_putendl_fd(message_to_print, STDERR_FILENO);
	free(message_to_print);
}

static int	add_envp_list(t_envp_list **head, char *key, char *value)
{
	t_envp_list	*new;
	t_envp_list	*tmp;

	new = malloc(sizeof(t_envp_list));
	if (new == NULL)
		return (1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

static int	set_env(char *key, char *value, t_minishell *data)
{
	if (att_existing_value(data->envp_list, key, value) == 0)
		add_envp_list(&data->envp_list, key, value);
	return (0);
}

static int	builtin_cd_util(char *args[], t_minishell *data, char **path)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd(RED"ERROR: "RST"cd: Too many arguments", STDERR_FILENO);
		return (1);
	}
	if (args[1] == NULL)
		*path = search_value(data->envp_list, "HOME");
	else
		*path = ft_strdup(args[1]);
	if (!*path[0])
	{
		ft_putendl_fd(RED"ERROR: "RST"cd: HOME not defined", STDERR_FILENO);
		free(*path);
		return (1);
	}
	return (0);
}

int	builtin_cd(char *args[], t_minishell *data)
{
	char	*path;
	char	*oldpwd;

	if (builtin_cd_util(args, data, &path) == 1)
	{
		free(path);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		oldpwd = search_value(data->envp_list, "PWD");
	if (chdir(path) == -1)
	{
		cd_print_error_message(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	free(path);
	set_env("OLDPWD", oldpwd, data);
	free(oldpwd);
	path = getcwd(NULL, 0);
	set_env("PWD", path, data);
	free(path);
	return (0);
}
