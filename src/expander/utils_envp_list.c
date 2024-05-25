/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:34:51 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/24 16:33:45 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	clear_list(t_node **head)
{
	if (*head)
	{
		clear_list(&(*head)->next);
		free((*head)->key);
		free((*head)->value);
		free((*head));
	}
	*head = NULL;
}

int	att_existing_value(t_node *head, char *key, char *value)
{
	t_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, -1) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*search_value(t_node *head, char *key)
{
	t_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, -1) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

int	envp_list_size(t_node *head)
{
	int		i;
	t_node	*aux;

	i = 0;
	aux = head;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
