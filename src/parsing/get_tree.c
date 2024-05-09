/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:44:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/09 18:45:05 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_token_list	*invert_list(t_token_list *head)
{
	t_token_list	*rest;

	if (head == NULL || head->next == NULL)
		return (head);
	rest = invert_list(head->next);
	head->next->next = head;
	head->next = NULL;
	return (rest);
}

t_exec_tree	*get_tree(t_token_list *token_list)
{
	t_token_list	*left;
	t_token_list	*right;

	token_list = invert_list(token_list);

}
