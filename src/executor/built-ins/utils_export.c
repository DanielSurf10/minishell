/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:29:48 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/14 15:52:50 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

int	key_exist(char *key, t_envp_list *envp_list)
{
	t_envp_list	*tmp;

	tmp = envp_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, -1) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	export_print_error_message(char *key_value)
{
	int			length;
	char		*message_to_print;
	const char	*message[2] = {RED"ERROR: "RST"export: '", \
								"': not a valid identifier"};

	length = ft_strlen(message[0]) + ft_strlen(key_value) \
						+ ft_strlen(message[1]) + 1;
	message_to_print = malloc(length);
	ft_strlcpy(message_to_print, message[0], length);
	ft_strlcat(message_to_print, key_value, length);
	ft_strlcat(message_to_print, message[1], length);
	ft_putendl_fd(message_to_print, STDERR_FILENO);
	free(message_to_print);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "?", -1) == 0)
			continue ;
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}

void	print_sorted_envp(t_minishell *data)
{
	int		i;
	int		j;
	char	*temp;
	char	**envp;

	envp = create_envp(data->envp_list);
	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], -1) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_envp(envp);
	free_envp(envp);
}
