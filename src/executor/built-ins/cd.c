/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:41:23 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/01 18:51:19 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static int add_envp_list(t_envp_list **head, char *key, char *value)
{
    t_envp_list *new;
    t_envp_list *tmp;

    new = malloc(sizeof(t_envp_list));
    if (new == NULL)
        return (1);
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    if (*head == NULL)
        *head = new;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (0);
}

static int set_env(char *key, char *value, t_minishell *data)
{
    if (att_existing_value(data->envp_list, key, value) == 0)
        add_envp_list(&data->envp_list, key, value);
    return (0);
}

int	builtin_cd(char *args[], t_minishell *data)
{
    char	*path;
    char	*oldpwd;

    if (args[1] == NULL)
        path = search_value(data->envp_list, "HOME");
    else
        path = ft_strdup(args[1]);
    if (path == NULL)
        return (1);
    oldpwd = getcwd(NULL, 0);
    if (oldpwd == NULL)
    {
        free(path);
        return (1);
    }
    if (chdir(path) == -1)
    {
        free(path);
        free(oldpwd);
        return (1);
    }
    free(path);
    set_env("OLDPWD", oldpwd, data);
    free(oldpwd);
    set_env("PWD", getcwd(NULL, 0), data);
    return (0);
}
