/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:51:07 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 22:25:08 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*mem;

	i = 0;
	if (!s)
		return (s);
	mem = (char *) s;
	while (i < n)
	{
		mem[i] = c;
		i++;
	}
	return (s);
}
