/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/24 16:46:52 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_valid_variable(char letter)
{
	return ((letter >= 'a' && letter <= 'z')
			|| (letter >= 'A' && letter <= 'Z')
			|| (letter >= '0' && letter <= '9')
			|| letter == '_');
}

char	*expand_string(char *str, t_node *head)
{
	int				i[2];
	int				in_quotes;
	char 			*key;
	char			*expanded;
	t_string_list	*new_str;

	i[0] = 0;
	in_quotes = 0;
	new_str = NULL;
	while (str[i[0]] != '\0')
	{
		if (str[i[0]] == '\'' && (in_quotes == 0 || in_quotes == 1))
			in_quotes = ternary(in_quotes == 0, 1, 0);
		else if (str[i[0]] == '\"' && (in_quotes == 0 || in_quotes == 2))
			in_quotes = ternary(in_quotes == 0, 2, 0);
		else if (str[i[0]] == '$' && in_quotes != 1)
		{

			// Isso aqui pode dar uma função separada
			// Começa aqui

			i[0]++;
			if (str[i[0]] >= '0' && str[i[0]] <= '9' || str[i[0]] == '$'
				|| is_valid_variable(str[i[0]]) == 0)
			{
				if (!(str[i[0]] >= '0' && str[i[0]] <= '9'))
				{
					while (is_valid_variable(str[i[0]]))
						i[0]++;
					if (str[i[0]] == '$')
						i[0]++;
					// if (str[i] == ' ' || str[i] == '\'' || str[i] == '"')
					if (is_valid_variable(str[i[0]]) == 0)
						i[0]--;
				}
			}
			else
			{
				i[1] = 0;
				while (is_valid_variable(str[i[0]]))
				{
					i[1]++;
					i[0]++;
				}
				key = ft_substr(str, i[0] - i[1], i[1]);
				expanded = search_value(head, key);
				add_string_to_list(&new_str, expanded);
				free(key);
				free(expanded);
				i[0]--;
			}

			// Termina aqui

		}
		else
			add_letter_list(&new_str, str[i[0]]);
		i[0]++;
	}
	expanded = create_string_from_list(new_str);
	clear_str_list(&new_str);
	return (expanded);
}
