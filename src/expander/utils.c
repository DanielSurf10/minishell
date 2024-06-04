/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:33:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/03 22:21:25 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	ternary(int condition, int if_true, int if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}

int	is_valid_var(char letter)
{
	return ((letter >= 'a' && letter <= 'z')
		|| (letter >= 'A' && letter <= 'Z')
		|| (letter >= '0' && letter <= '9')
		|| letter == '_');
}

char	*remove_quotes(char	*delimiter)
{
	int			i;
	int			in_quotes;
	char		*expanded;
	t_str_list	*new_str;

	i = 0;
	in_quotes = 0;
	new_str = NULL;
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == '\'' && (in_quotes == 0 || in_quotes == 1))
			in_quotes = ternary(in_quotes == 0, 1, 0);
		else if (delimiter[i] == '\"' && (in_quotes == 0 || in_quotes == 2))
			in_quotes = ternary(in_quotes == 0, 2, 0);
		else
			add_letter_list(&new_str, delimiter[i]);
		i++;
	}
	expanded = create_string_from_list(new_str);
	clear_str_list(&new_str);
	return (expanded);
}
