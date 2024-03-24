/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:13:38 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 22:30:41 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*mem_s1;
	unsigned char	*mem_s2;

	i = 0;
	mem_s1 = (unsigned char *) s1;
	mem_s2 = (unsigned char *) s2;
	if (!n)
		return (0);
	while (i < n - 1 && mem_s1[i] == mem_s2[i])
		i++;
	return (mem_s1[i] - mem_s2[i]);
}
