/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:57:07 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/27 18:06:07 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux1;
	t_list	*aux2;

	if (lst)
	{
		aux1 = *lst;
		while (aux1)
		{
			aux2 = aux1->next;
			ft_lstdelone(aux1, del);
			aux1 = aux2;
		}
		*lst = NULL;
	}
}
