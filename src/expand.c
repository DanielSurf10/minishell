/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/21 16:17:11 by leobarbo         ###   ########.fr       */
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

void	print_string(t_expand_list *head)
{
	t_expand_list	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%c", temp->letter);
		temp = temp->next;
	}
	printf("\n");
}

char	*expand(char *str, t_node *head)
{
	// char	*new_str;
	char 	*key;
	char	*expanded;
	int		i;
	int		k;
	t_expand_list	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] >= '0' && str[i] <= '9' || str[i] == '$' || is_valid_variable(str[i]) == 0)	// Isso tá meio estranho
			{
				while (is_valid_variable(str[i]))	// Isso pode mudar
					i++;
				if (str[i] == '$')
					i++;
				continue ;
			}

			k = 0;
			while (is_valid_variable(str[i]))
			{
				k++;
				i++;
			}
			// new_str = malloc(sizeof(char) * (k + 1));

			key = ft_substr(str, i - k, k);
			expanded = search_value(head, key);

			add_string_to_list(&new_str, expanded);

			free(key);
			free(expanded);
		}
		else
		{
			add_letter_list(&new_str, str[i]);
			i++;
		}
	}

	print_string(new_str);

	return (NULL);		// MUDAR ISSO AQUIIII
}
