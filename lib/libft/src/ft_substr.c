/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:32:13 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 22:36:41 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size_s;
	size_t	size_new;
	char	*new;

	size_s = ft_strlen(s);
	if (start >= size_s)
		size_new = 0;
	else
	{
		size_s = ft_strlen(s + start);
		if (size_s >= len)
			size_new = len;
		else
			size_new = size_s;
	}
	new = (char *) malloc(size_new + 1);
	if (!new)
		return (NULL);
	if (size_new == 0)
		new[0] = '\0';
	else
		ft_strlcpy(new, s + start, size_new + 1);
	return (new);
}
