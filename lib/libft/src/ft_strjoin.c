/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:52:49 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 22:34:36 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_all;
	char	*join;

	size_all = ft_strlen(s1) + ft_strlen(s2);
	join = 0;
	size_all++;
	join = (char *) malloc(size_all);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, size_all);
	ft_strlcat(join, s2, size_all);
	return (join);
}
