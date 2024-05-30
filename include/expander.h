/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:07:05 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/30 16:33:15 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include "minishell.h"

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

typedef struct s_envp_list
{
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}	t_envp_list;

typedef struct s_expand_list
{
	char					letter;
	struct s_expand_list	*next;
}	t_str_lst;

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

//****************************************************************************//
//                                 envp_list                                  //
//****************************************************************************//

t_envp_list	*env_create_node(char *key, char *value);
void		env_insert_node(t_envp_list **head, char *key, char *value);
t_envp_list	*store_to_list(char *envp[]);
char		**create_envp(t_envp_list *head);
void		env_delete_value(t_envp_list **head, char *key);

//****************************************************************************//
//                               expand_string                                //
//****************************************************************************//

char		*expand_string(char *str, t_envp_list *head);

//****************************************************************************//
//                                string_list                                 //
//****************************************************************************//

void		add_letter_list(t_str_lst **lst, char letter);
int			size_list(t_str_lst *lst);
void		add_string_to_list(t_str_lst **lst, char *str);
void		clear_str_list(t_str_lst **head);
char		*create_string_from_list(t_str_lst *lst);

//****************************************************************************//
//                              utils_envp_list                               //
//****************************************************************************//

void		clear_list(t_envp_list **head);
int			att_existing_value(t_envp_list *head, char *key, char *value);
char		*search_value(t_envp_list *head, char *key);
int			envp_list_size(t_envp_list *head);
void		free_envp(char **envp);

//****************************************************************************//
//                                   utils                                    //
//****************************************************************************//

int			ternary(int condition, int if_true, int if_false);

#endif
