/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:07:05 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/21 15:12:03 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

# include <stdio.h>
# include <stdlib.h>

typedef struct s_node
{
	char			*key;
	char 			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_expand_list
{
	char					letter;
	struct s_expand_list	*next;
}					t_expand_list;

t_node	*env_create_node(char *key, char *value);
void	env_insert_node(t_node **head, char *key, char *value);
t_node	*store_to_list(char *envp[]);
t_node	*envp_to_list(char *envp[]);
char	*expand(char *str, t_node *head);
void	printList(t_node *head);
void	clear_list(t_node **head);
void	env_delete_value(t_node **head, char *key);
int		exist_in_list(t_node *head, char *key, char *value);
void	env_malloc(int size, char **dest);
char	**create_envp(t_node *head);
int		envp_list_size(t_node *head);
void	free_envp(char **envp);
char	*search_value(t_node *head, char *key);

#endif
