/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:46 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/24 17:44:32 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_node	*env_create_node(char *key, char *value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	env_insert_node(t_node **head, char *key, char *value)
{
	t_node	*new_node;
	t_node	*temp;

	if (att_existing_value(*head, key, value) == 1)
		return ;
	new_node = env_create_node(key, value);
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_node	*store_to_list(char *envp[])
{
	int		idx[3];
	char	*key;
	char	*value;
	t_node	*head;

	head = NULL;
	idx[0] = -1;
	while (envp[++idx[0]])
	{
		idx[1] = 0;
		while (envp[idx[0]][idx[1]] != '=')
			idx[1]++;
		key = malloc(sizeof(char) * (idx[1] + 1));
		idx[2] = idx[1] + 1;
		while (envp[idx[0]][idx[2]] != '\0')
			idx[2]++;
		value = malloc(sizeof(char) * (idx[2] + 1));
		ft_strlcpy(key, envp[idx[0]], idx[1] + 1);
		ft_strlcpy(value, envp[idx[0]] + idx[1] + 1, idx[2]);
		env_insert_node(&head, key, value);
	}
	return (head);
}

char	**create_envp(t_node *head)
{
	int		i;
	int		full_size;
	char	**new_envp;
	t_node	*temp;

	i = 0;
	temp = head;
	new_envp = malloc(sizeof(char *) * (envp_list_size(head) + 1));
	while (temp != NULL)
	{
		full_size = ft_strlen(temp->key) + ft_strlen(temp->value) + 2;
		new_envp[i] = malloc(sizeof(char) * full_size);
		ft_strlcpy(new_envp[i], temp->key, full_size);
		ft_strlcat(new_envp[i], "=", full_size);
		ft_strlcat(new_envp[i], temp->value, full_size);
		i++;
		temp = temp->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	env_delete_value(t_node **head, char *key)
{
	t_node	*temp;
	t_node	*prev;

	temp = *head;
	prev = NULL;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, -1) == 0)
		{
			if (prev == NULL)
				*head = temp->next;
			else
				prev->next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}
