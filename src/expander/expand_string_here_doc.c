/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_here_doc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:18:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/04 17:59:31 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	skip_invalid_variable(char *str, int *i)
{
	if (!(str[*i] >= '0' && str[*i] <= '9'))
	{
		while (is_valid_var(str[*i]))
			(*i)++;
		if (str[*i] == '$')
			(*i)++;
		if (is_valid_var(str[*i]) == 0)
			(*i)--;
	}
}

static void	expand_variable_heredoc(char *str, int *i, t_str_list **new_str, \
									t_envp_list *envp_list)
{
	int		k;
	char	*key;
	char	*expanded;

	(*i)++;
	if (str[*i] >= '0' && str[*i] <= '9' || str[*i] == '$'
		|| is_valid_var(str[*i]) == 0)
		skip_invalid_variable(str, i);
	else
	{
		k = 0;
		while (is_valid_var(str[*i]))
		{
			k++;
			(*i)++;
		}
		key = ft_substr(str, (*i) - k, k);
		expanded = search_value(envp_list, key);
		add_string_to_list(new_str, expanded);
		free(key);
		free(expanded);
		(*i)--;
	}
}

char	*expand_string_heredoc(char *str, t_envp_list *envp_list)
{
	int			i;
	char		*expanded;
	t_str_list	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			expand_variable_heredoc(str, &i, &new_str, envp_list);
		else
			add_letter_list(&new_str, str[i]);
		i++;
	}
	expanded = create_string_from_list(new_str);
	clear_str_list(&new_str);
	return (expanded);
}
