/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/22 19:29:59 by danbarbo         ###   ########.fr       */
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

void	print_string(t_expand_list *head)		// TIRAR DPS
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
char	*remote_quotes(char *str)
{
	int				i;
	char			*new_string;
	t_expand_list	*new_str_list;

	i = 0;
	new_str_list = NULL;

	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				add_letter_list(&new_str_list, str[i]);
				i++;
			}
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				add_letter_list(&new_str_list, str[i]);
				i++;
			}
		}
		else
			add_letter_list(&new_str_list, str[i]);

		i++;
	}

	new_string = create_string_from_list(new_str_list);

	clear_str_list(&new_str_list);

	return (new_string);
}

// fora das aspas = 0
// aspas simples = 1
// aspas duplas = 2
char	*expand(char *str, t_node *head)
{
	// char	*new_str;
	int				i;
	int				k;
	int				in_quotes;
	char 			*key;
	char			*expanded;
	char			*expanded_without_quotes;
	t_expand_list	*new_str;

	i = 0;
	in_quotes = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && (in_quotes == 0 || in_quotes == 1))
		{
			if (in_quotes == 0)
				in_quotes = 1;
			else if (in_quotes == 1)
				in_quotes = 0;
			i++;
			continue ;
		}
		else if (str[i] == '\"' && (in_quotes == 0 || in_quotes == 2))
		{
			if (in_quotes == 0)
				in_quotes = 2;
			else if (in_quotes == 2)
				in_quotes = 0;
			i++;
			continue ;
		}

		if (str[i] == '$' && in_quotes != 1)
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

	// print_string(new_str);

	expanded = create_string_from_list(new_str);

	// expanded_without_quotes = remote_quotes(expanded);	// ARRUMAR ISSO AQUI
	expanded_without_quotes = ft_strdup(expanded);

	free(expanded);

	clear_str_list(&new_str);

	return (expanded_without_quotes);		// MUDAR ISSO AQUIIII
}
