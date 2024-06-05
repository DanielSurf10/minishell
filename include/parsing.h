/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:32:16 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/05 00:56:49 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include "lexing.h"
# include "expander.h"
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

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

t_exec_tree	*get_tree(t_token_list *token_list, t_minishell *data);
void		free_tree(t_exec_tree **tree);
void		free_tree_all(t_exec_tree **tree);

char		*create_here_doc(char *delimiter, t_minishell *data);

#endif
