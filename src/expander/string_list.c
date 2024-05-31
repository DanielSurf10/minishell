/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:21:39 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/30 22:35:43 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	add_letter_list(t_str_list **lst, char letter)
{
	t_str_list	*node;
	t_str_list	*last_node;

	last_node = *lst;
	node = malloc(sizeof(t_str_list));
	node->letter = letter;
	node->next = NULL;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = node;
	else
		*lst = node;
}

int	size_list(t_str_list *lst)
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

void	add_string_to_list(t_str_list **lst, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		add_letter_list(lst, str[i]);
		i++;
	}
}

void	clear_str_list(t_str_list **head)
{
	t_str_list	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

char	*create_string_from_list(t_str_list *lst)
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
