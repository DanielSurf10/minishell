/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:02:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/01 19:02:57 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int    builtin_unset(char *key, t_envp_list **envp_list)
{
    t_envp_list *tmp;
    t_envp_list *prev;

    tmp = *envp_list;
    prev = NULL;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, -1) == 0)
        {
            if (prev)
                prev->next = tmp->next;
            else
                *envp_list = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return (0);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (0);
}