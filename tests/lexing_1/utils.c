/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:42:42 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/30 19:53:10 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_metacharacter(char character)
{
	if (character == '('
		|| character == ')'
		|| character == '|'
		|| character == '&'
		|| character == '<'
		|| character == '>'
		|| character == '\''
		|| character == '\"'
		|| ft_isspace(character))
		return (1);
	return (0);
}
