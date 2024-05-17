/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/17 16:18:13 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_node	*env_create_node(char *key, char *value)
{
	t_node	*new_node;

	new_node = (t_node*)malloc(sizeof(t_node));
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	env_insert_node(t_node **head, char *key, char *value)
{
	t_node *new_node;
	t_node *temp;

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

void	printList(t_node *head)
{
	t_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("Key: %s, Value: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

// typedef struct s_aux_envp
// {
	// char			*new_string;
// 	char			*key;
// 	char 			*value;
// 	int				i;
// 	int				j;
// 	int				k;
// }					t_aux_envp;



/*Cria um lista a partir do envp
*/
t_node	*store_to_list(char *envp[])
{
	t_node		*head;
	char	*key;
	char	*value;
	int		i;
	int		j;
	int		k;

	head = NULL;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		env_malloc(j + 1, &key);
		k = j + 1;
		while (envp[i][k] != '\0')
			k++;
		env_malloc(k + 1, &value);
		ft_strlcpy(key, envp[i], j + 1);
		ft_strlcpy(value, envp[i] + j + 1, k);
		env_insert_node(&head, key, value);
	}
	return (head);
}

char	**create_envp(t_node *head)
{
	int		i;
	t_node	*temp;
	char	**new_envp;

	i = 0;
	temp = head;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	temp = head;
	while (temp != NULL)
	{
		new_envp[i] = ft_strjoin(temp->key, temp->value); // colocar sinal de "=" entre key e value
		i++;
		temp = temp->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	*expand(char *str, t_node *head)
{
	t_node	*temp;
	char	*new_str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	temp = head;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] != ' ' && str[i] != '\0')
			{
				k++;
				i++;
			}
			// env_malloc(k + 1, &new_str);
			new_str = malloc(sizeof(char) * (k + 1));


			// while (str[j] != '$')
			// 	ft_strcpy(new_str, str, j);
			// {
			// 	new_str[j] = str[j];
			// 	j++;
			// }
			while (temp != NULL)
			{
				if (ft_strncmp(temp->key, &str[j], k) == 0)
				{
					new_str = ft_strjoin(new_str, temp->value);
					j = j + k;
					break ;
				}
				temp = temp->next;
			}
			k = 0;
		}
		i++;
	}
	return (new_str);
}


int main(int argc, char *argv[], char *envp[]) {
	t_node	*list_envp;
	char	**new_envp;
	char	*expanded;

	list_envp = store_to_list(envp);

	// printList(list_envp);

	env_insert_node(&list_envp, "teste", "bomdia");

	new_envp = create_envp(list_envp);

	// expanded = expand("ola $teste", list_envp);		// ola bomdia

	printList(list_envp);
	return (0);
}
