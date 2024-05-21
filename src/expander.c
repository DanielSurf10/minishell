/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:46 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/21 15:35:24 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_node	*env_create_node(char *key, char *value)
{
	t_node	*new_node;

	new_node = (t_node*)malloc(sizeof(t_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	env_insert_node(t_node **head, char *key, char *value)
{
	t_node *new_node;
	t_node *temp;

	if (exist_in_list(*head, key, value) == 1)
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

/*
Cria um lista a partir do envp
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
		key = malloc(sizeof(char) * (j + 1));
		k = j + 1;
		while (envp[i][k] != '\0')
			k++;
		value = malloc(sizeof(char) * (k + 1));
		ft_strlcpy(key, envp[i], j + 1);
		ft_strlcpy(value, envp[i] + j + 1, k);
		env_insert_node(&head, key, value);
	}
	return (head);
}

char	**create_envp(t_node *head)
{
	int		i;
	int		full_size;
	t_node	*temp;
	char	**new_envp;

	i = 0;
	temp = head;
	new_envp = malloc(sizeof(char *) * (envp_list_size(head) + 1));
	while (temp != NULL)
	{
		full_size = ft_strlen(temp->key) + ft_strlen(temp->value) + 2;		// tamando da chave + tamanho do valor + 1 para o sinal de "=" + 1 para o \0
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
// Funcao expander dividida em duas funcoes, porem esta dando seg fault

// typedef struct s_exp_aux
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;
// 	int		k;
// }				t_exp_aux;

// void	aux_expan(t_exp_aux *exp_aux, char *str, t_node *temp)
// {
// 	if (str[exp_aux->i] == '$')
// 	{
// 		exp_aux->i++;
// 		while (str[exp_aux->i] != ' ' && str[exp_aux->i] != '\0')
// 		{
// 			exp_aux->k++;
// 			exp_aux->i++;
// 		}
// 		env_malloc(exp_aux->k + 1, &exp_aux->new_str);
// 		exp_aux->new_str = malloc(sizeof(char) * (exp_aux->k + 1));


// 		while (str[exp_aux->j] != '$')
// 			ft_strlcpy(exp_aux->new_str, str, exp_aux->j);
// 		{
// 			exp_aux->new_str[exp_aux->j] = str[exp_aux->j];
// 			exp_aux->j++;
// 		}
// 	}
// }

// char	*expand(char *str, t_node *head)
// {
// 	t_node	*temp;
// 	t_exp_aux	*exp_aux;

// 	temp = head;
// 	while (str[exp_aux->i] != '\0')
// 	{
// 		aux_expan(exp_aux, str, temp);
// 		while (temp != NULL)
// 		{
// 			if (ft_strncmp(temp->key, &str[exp_aux->j], exp_aux->k) == 0)
// 			{
// 				exp_aux->new_str = ft_strjoin(exp_aux->new_str, temp->value);
// 				exp_aux->j = exp_aux->j + exp_aux->k;
// 				break ;
// 			}
// 			temp = temp->next;
// 		}
// 		exp_aux->k = 0;
// 	}
// 	exp_aux->i++;
// 	return (exp_aux->new_str);
// }
