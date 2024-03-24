/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:46:26 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/20 14:37:24 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elem, size_t size)
{
	char	*mem;

	if ((num_elem * size) != 0 && (num_elem * size) / size != num_elem)
		return (NULL);
	mem = (char *) malloc(num_elem * size);
	if (mem != NULL)
		ft_bzero(mem, num_elem * size);
	return (mem);
}
