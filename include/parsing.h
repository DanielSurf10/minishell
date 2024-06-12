/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:32:16 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/11 20:38:41 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include "lexing.h"
# include "expander.h"
# include "executor.h"
# include "minishell.h"

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

typedef struct s_exec_tree
{
	int					type;
	t_token_list		*command;
	struct s_exec_tree	*subshell;
	struct s_exec_tree	*left;
	struct s_exec_tree	*right;
}	t_exec_tree;

typedef struct s_aux_tree
{
	int				i;
	int				idx_parenthesis;
	int				and_or_indice;
	int				pipe_indice;
	int				redir_counter;
	t_token_list	*aux;
	t_token_list	*aux2;
	t_token_list	*args;
	t_token_list	*redir_list;
	t_token_list	*sub_list_left;
	t_token_list	*sub_list_right;
	t_exec_tree		*tree;
}	t_aux_tree;

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

t_exec_tree	*get_tree(t_token_list *token_list, t_minishell *data);
void		*free_tree(t_exec_tree **tree);
void		*free_tree_all(t_exec_tree **tree);

char		*create_here_doc(char *delimiter, t_minishell *data);

//****************************************************************************//
//                                  get_tree                                  //
//****************************************************************************//

int			index_to_close_parenthesis(t_token_list *token_list);
int			index_to_open_parenthesis(t_token_list *token_list);
t_exec_tree	*make_tree_cmd_recursive(t_token_list *redir_list, \
				t_token_list *args, t_minishell *data);
t_exec_tree	*make_tree_cmd(t_token_list *token_list, t_minishell *data);
t_exec_tree	*make_tree(t_token_list *token_list, t_minishell *data);
t_exec_tree	*get_tree(t_token_list *token_list, t_minishell *data);

#endif
