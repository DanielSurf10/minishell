/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/23 19:18:43 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	is_valid_variable(char letter)
{
	return ((letter >= 'a' && letter <= 'z')
			|| (letter >= 'A' && letter <= 'Z')
			|| (letter >= '0' && letter <= '9')
			|| letter == '_');
}

void	add_letter_list(t_expand_list **lst, char letter)
{
	t_expand_list	*node;
	t_expand_list	*last_node;

	last_node = *lst;
	node = malloc(sizeof(t_expand_list));
	node->letter = letter;
	node->next = NULL;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = node;
	else
		*lst = node;
}

void	add_string_to_list(t_expand_list **lst, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		add_letter_list(lst, str[i]);
		i++;
	}
}

// void	print_string(t_expand_list *head)		// TIRAR DPS
// {
// 	t_expand_list	*temp;
//
// 	temp = head;
// 	while (temp != NULL)
// 	{
// 		printf("%c", temp->letter);
// 		temp = temp->next;
// 	}
// 	printf("\n");
// }

void	clear_str_list(t_expand_list **head)
{
	t_expand_list	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

int	size_list(t_expand_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char 	*create_string_from_list(t_expand_list *lst)
{
	int		i;
	int		size_str;
	char	*str;

	i = 0;
	size_str = size_list(lst);
	str = malloc(sizeof(char) * (size_str + 1));
	while (lst)
	{
		str[i] = lst->letter;
		lst = lst->next;
		i++;
	}
	str[i] = '\0';
	return (str);
}

// fora das aspas = 0
// aspas simples = 1
// aspas duplas = 2
char	*expand(char *str, t_node *head)
{
	int				i;
	int				k;
	int				in_quotes;
	char 			*key;
	char			*expanded;
	t_expand_list	*new_str;

	i = 0;
	in_quotes = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && (in_quotes == 0 || in_quotes == 1))
			in_quotes = ternary(in_quotes == 0, 1, 0);
		else if (str[i] == '\"' && (in_quotes == 0 || in_quotes == 2))
			in_quotes = ternary(in_quotes == 0, 2, 0);
		else if (str[i] == '$' && in_quotes != 1)
		{

			// Isso aqui pode dar uma função separada
			// Começa aqui

			i++;
			if (str[i] >= '0' && str[i] <= '9' || str[i] == '$'
				|| is_valid_variable(str[i]) == 0)
			{
				while (is_valid_variable(str[i]))
					i++;
				if (str[i] == '$')
					i++;
			}
			else
			{
				k = 0;
				while (is_valid_variable(str[i]))
				{
					k++;
					i++;
				}
				key = ft_substr(str, i - k, k);
				expanded = search_value(head, key);
				add_string_to_list(&new_str, expanded);
				free(key);
				free(expanded);
				i--;
			}

			// Termina aqui

		}
		else
			add_letter_list(&new_str, str[i]);
		i++;
	}
	expanded = create_string_from_list(new_str);
	clear_str_list(&new_str);
	return (expanded);
}
