/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:51:45 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 22:23:26 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*mem_src;
	char	*mem_dst;

	i = 0;
	mem_src = (char *) src;
	mem_dst = (char *) dest;
	if (!dest || !src)
		return (dest);
	while (i < n)
	{
		mem_dst[i] = mem_src[i];
		i++;
	}
	return (dest);
}
