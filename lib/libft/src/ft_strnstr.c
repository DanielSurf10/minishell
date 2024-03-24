/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:04:19 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 21:42:18 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i_str;
	size_t	i_to_find;

	i_str = 0;
	i_to_find = 0;
	if (!str || !to_find)
		return (NULL);
	if (!to_find[0])
		return ((char *) str);
	while (str[i_str] && to_find[i_to_find] && i_str < n)
	{
		while (i_str + i_to_find < n && to_find[i_to_find]
			&& str[i_to_find + i_str] == to_find[i_to_find])
			i_to_find++;
		if (!to_find[i_to_find])
			return (((char *) str) + i_str);
		i_to_find = 0;
		i_str++;
	}
	return (NULL);
}
