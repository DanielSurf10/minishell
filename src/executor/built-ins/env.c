/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:22:38 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/18 16:47:19 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	builtin_env(t_minishell *data)
{
	t_envp_list	*tmp;

	tmp = data->envp_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "?", -1) != 0)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
