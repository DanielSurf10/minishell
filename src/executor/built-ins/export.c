/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:48:52 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/17 12:48:38 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

static void	update_envp(char *key, char *value, t_envp_list *envp_list)
{
	t_envp_list	*tmp;

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
	t_envp_list	*new;
	t_envp_list	*tmp;

	new = malloc(sizeof(t_envp_list));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	tmp = envp_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	set_arg(char *arg, int idx, t_envp_list *envp_list)
{
	int		ret_code;
	char	*key;
	char	*value;

	ret_code = 0;
	key = ft_substr(arg, 0, idx);
	value = ft_substr(arg, idx + 1, ft_strlen(arg) - idx);
	if (key && key[0] && value && key_is_valid(key))
	{
		if (key_exist(key, envp_list))
			update_envp(key, value, envp_list);
		else
			add_envp(key, value, envp_list);
	}
	else
	{
		export_print_error_message(arg);
		ret_code = 1;
	}
	free(key);
	free(value);
	return (ret_code);
}

int	select_arg(char *arg, t_envp_list *envp_list)
{
	int	i;
	int	ret_code;

	i = 0;
	ret_code = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		ret_code = set_arg(arg, i, envp_list);
	else if (arg[i] == '\0' && !key_is_valid(arg))
		ret_code = 1;
	return (ret_code);
}

int	builtin_export(char **argv, t_minishell *data)
{
	int		i;
	int		ret_code;

	i = 1;
	ret_code = 0;
	if (!argv[1])
		print_sorted_envp(data);
	else
	{
		while (argv[i])
		{
			ret_code = select_arg(argv[i], data->envp_list);
			i++;
		}
	}
	return (ret_code);
}
