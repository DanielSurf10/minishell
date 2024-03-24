/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:04:25 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/21 16:58:07 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	letter_is(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	first;
	size_t	len;

	first = 0;
	len = ft_strlen(str);
	while (letter_is(str[first], set))
		first++;
	while (letter_is(str[len - 1], set))
		len--;
	return (ft_substr(str, first, len - first));
}
