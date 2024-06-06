/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:48:52 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/06 20:16:48 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

static void	print_error_message(char *key_value)
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

static int key_exist(char *key, t_envp_list *envp_list)
{
	t_envp_list *tmp;

	tmp = envp_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, -1) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	update_envp(char *key, char *value, t_envp_list *envp_list)
{
	t_envp_list *tmp;

	tmp = envp_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, -1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	add_envp(char *key, char *value, t_envp_list *envp_list)
{
	t_envp_list *new;
	t_envp_list *tmp;

	new = malloc(sizeof(t_envp_list));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	tmp = envp_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	select_arg(char *arg, t_envp_list *envp_list)
{
	int		i;
	int		ret_code;
	char	*key;
	char	*value;
	char	*expandend;

// 	i = 0;
// 	value = ft_strnstr(arg, "=", ft_strlen(arg));
// 	arg[value - arg] = '\0';
// 	value++;
// 	key = arg;

	i = 0;
	ret_code = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
	{
		key = ft_substr(arg, 0, i);
		value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
		if (key && value && key_is_valid(key))
		{
			if (key_exist(key, envp_list))
				update_envp(key, value, envp_list);
			else
				add_envp(key, value, envp_list);
		}
		else
		{
			print_error_message(arg);
			ret_code = 1;
		}
		free(key);
		free(value);
	}

	return (ret_code);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "?", -1) == 0)
			continue;
		ft_putendl_fd(envp[i], STDIN_FILENO);
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

int	builtin_export(char **argv, t_minishell *data)
{
	int		i;
	int		ret_code;
	char	*key;
	char	*value;

	i = 1;
	ret_code = 0;
	if (!argv[1])
		print_sorted_envp(data);
	else
		while(argv[i])
		{
			ret_code = select_arg(argv[i], data->envp_list);
			i++;
		}
	return (ret_code);
}
