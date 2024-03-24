/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:51:49 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 06:15:22 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_src;
	size_t	size_dst;

	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	if (size <= size_dst)
		return (size + size_src);
	size -= size_dst;
	ft_strlcpy(dst + size_dst, src, size);
	return (size_src + size_dst);
}
