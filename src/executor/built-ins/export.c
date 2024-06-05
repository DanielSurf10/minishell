/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:02:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/01 19:02:57 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"


static int key_exist(char *key, t_envp_list *envp_list)
{
    t_envp_list *tmp;

    tmp = envp_list;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, -1) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

static int key_is_valid(char *key)
{
    int i;

    i = 0;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void    update_envp(char *key, char *value, t_envp_list *envp_list)
{
    t_envp_list *tmp;

    tmp = envp_list;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, -1) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
}

static void    add_envp(char *key, char *value, t_envp_list *envp_list)
{
    t_envp_list *new;
    t_envp_list *tmp;

    new = malloc(sizeof(t_envp_list));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    tmp = envp_list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

int builtin_export(char *argv, t_minishell *data)
{
    char *key;
    char *value;
    int i;

    i = 0;
    while(argv[i])
    {
        if (argv[i] == '=')
        {
            key = ft_substr(argv, 0, i);
            value = ft_substr(argv, i + 1, ft_strlen(argv) - i);
            if (key && value && key_is_valid(key) && key[0] != '_')
            {
                if (key_exist(key, data->envp_list))
                    update_envp(key, value, data->envp_list);
                else
                    add_envp(key, value, data->envp_list);
                free(key);
                free(value);
            }
            else
                return (1);
            free(key);
            free(value);
        }
        i++;
    }
    return (0);
}