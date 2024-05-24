/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:07:05 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/24 16:43:38 by danbarbo         ###   ########.fr       */
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
}					t_string_list;

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

t_node	*env_create_node(char *key, char *value);
void	env_insert_node(t_node **head, char *key, char *value);
t_node	*store_to_list(char *envp[]);
t_node	*envp_to_list(char *envp[]);
char	*expand_string(char *str, t_node *head);
void	printList(t_node *head);
void	clear_list(t_node **head);
void	env_delete_value(t_node **head, char *key);
int		att_existing_value(t_node *head, char *key, char *value);
char	**create_envp(t_node *head);
int		envp_list_size(t_node *head);
void	free_envp(char **envp);
char	*search_value(t_node *head, char *key);
char 	*create_string_from_list(t_string_list *lst);
int		size_list(t_string_list *lst);
void	add_string_to_list(t_string_list **lst, char *str);
void	clear_str_list(t_string_list **head);
void	add_letter_list(t_string_list **lst, char letter);

// Utils
int		ternary(int condition, int if_true, int if_false);		// ARRUMAR ESSA BOSTA: colocar no minishell.h

#endif
