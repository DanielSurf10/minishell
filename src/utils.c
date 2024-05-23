/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:34:51 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/23 18:59:11 by danbarbo         ###   ########.fr       */
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

/*Função para deletar um nó da lista, caso a chave(key) exista*/
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

/* Funcão para procurar se a chave(key) existe. Caso exista, vai apenas alterar o valor
da chave e retornar '1'*/
int	exist_in_list(t_node *head, char *key, char *value)
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

void	env_malloc(int size, char **dest)
{
	*dest = (char *)malloc(sizeof(char) * size);
	if (*dest == NULL)
		return ;
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

int	ternary(int condition, int if_true, int if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}
