/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:07:05 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/24 17:44:13 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_expand_list
{
	char					letter;
	struct s_expand_list	*next;
}					t_str_lst;

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

//****************************************************************************//
//                                 envp_list                                  //
//****************************************************************************//

t_node	*env_create_node(char *key, char *value);
void	env_insert_node(t_node **head, char *key, char *value);
t_node	*store_to_list(char *envp[]);
char	**create_envp(t_node *head);
void	env_delete_value(t_node **head, char *key);

//****************************************************************************//
//                               expand_string                                //
//****************************************************************************//

char	*expand_string(char *str, t_node *head);

//****************************************************************************//
//                                string_list                                 //
//****************************************************************************//

void	add_letter_list(t_str_lst **lst, char letter);
int		size_list(t_str_lst *lst);
void	add_string_to_list(t_str_lst **lst, char *str);
void	clear_str_list(t_str_lst **head);
char	*create_string_from_list(t_str_lst *lst);

//****************************************************************************//
//                               utils_envp_list                              //
//****************************************************************************//

void	clear_list(t_node **head);
int		att_existing_value(t_node *head, char *key, char *value);
char	*search_value(t_node *head, char *key);
int		envp_list_size(t_node *head);
void	free_envp(char **envp);

//****************************************************************************//
//                                    utils                                   //
//****************************************************************************//

int		ternary(int condition, int if_true, int if_false);

#endif
