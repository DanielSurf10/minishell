/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:08:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/01 15:44:27 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_valid_var(char letter)
{
	return ((letter >= 'a' && letter <= 'z')
		|| (letter >= 'A' && letter <= 'Z')
		|| (letter >= '0' && letter <= '9')
		|| letter == '_');
}

static void	invalid_var(char *str, int *i)
{
	if (!(str[(*i)] >= '0' && str[(*i)] <= '9'))
	{
		while (is_valid_var(str[(*i)]))
			(*i)++;
		if (str[(*i)] == '$')
			(*i)++;
		if (is_valid_var(str[(*i)]) == 0)
			(*i)--;
	}
}

static void	expand_var(char *str, int *i, t_envp_list *head, \
	t_str_list **new_str)
{
	int		j;
	char	*key;
	char	*expanded;

	j = 0;
	while (is_valid_var(str[*i]) || (j == 0 && str[*i] == '?'))
	{
		j++;
		(*i)++;
	}
	key = ft_substr(str, (*i) - j, j);
	expanded = search_value(head, key);
	add_string_to_list(new_str, expanded);
	free(key);
	free(expanded);
	(*i)--;
}

static void	var_validation(int *i, char *str, \
	t_envp_list *head, t_str_list **new_str)
{
	(*i)++;
	if (str[*i] >= '0' && str[*i] <= '9' || str[*i] == '$'
		|| (is_valid_var(str[*i]) == 0 && str[*i] != '?'))
		invalid_var(str, i);
	else
		expand_var(str, i, head, new_str);
}

char	*expand_string(char *str, t_envp_list *head)
{
	int				i;
	int				in_quotes;
	char			*key;
	char			*expanded;
	t_str_list		*new_str;

	i = 0;
	in_quotes = 0;
	new_str = NULL;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\'' && (in_quotes == 0 || in_quotes == 1))
			in_quotes = ternary(in_quotes == 0, 1, 0);
		else if (str[i] == '\"' && (in_quotes == 0 || in_quotes == 2))
			in_quotes = ternary(in_quotes == 0, 2, 0);
		else if (str[i] == '$' && in_quotes != 1)
			var_validation(&i, str, head, &new_str);
		else
			add_letter_list(&new_str, str[i]);
		i++;
	}
	expanded = create_string_from_list(new_str);
	clear_str_list(&new_str);
	return (expanded);
}
