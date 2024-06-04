/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_here_doc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:18:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/03 23:12:02 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_string_heredoc(char *str, t_envp_list *envp_list)
{
	int			i;
	int			k;
	int			in_quotes;
	char		*key;
	char		*expanded;
	t_str_list	*new_str;

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
				|| is_valid_var(str[i]) == 0)
			{
				if (!(str[i] >= '0' && str[i] <= '9'))
				{
					while (is_valid_var(str[i]))
						i++;
					if (str[i] == '$')
						i++;
					// if (str[i] == ' ' || str[i] == '\'' || str[i] == '"')
					if (is_valid_var(str[i]) == 0)
						i--;
				}
			}
			else
			{
				k = 0;
				while (is_valid_var(str[i]))
				{
					k++;
					i++;
				}
				key = ft_substr(str, i - k, k);
				expanded = search_value(envp_list, key);
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
