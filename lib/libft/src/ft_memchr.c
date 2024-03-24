/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:54:03 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 06:37:08 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	i = 0;
	mem = (unsigned char *) s;
	if (!s)
		return (NULL);
	while (i < n && mem[i] != (unsigned char) c)
		i++;
	if (i == n)
		return (NULL);
	return ((void *) s + i);
}
