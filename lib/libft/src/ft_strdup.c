/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:13:05 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/17 00:56:54 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	i = ft_strlen((char *) s) + 1;
	dup = malloc(i);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, i);
	return (dup);
}
