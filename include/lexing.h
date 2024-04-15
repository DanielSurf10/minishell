/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:36:39 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/15 17:52:15 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

//****************************************************************************//
//                                  Includes                                  //
//****************************************************************************//

# include <stdlib.h>
# include "libft.h"

//****************************************************************************//
//                                   Enums                                    //
//****************************************************************************//

enum e_token
{
	WORD,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_HEREDOC,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND,
	OR,
	AND,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	EXPRESSION,
	COMMAND
};

//****************************************************************************//
//                                  Structs                                   //
//****************************************************************************//

//****************************************************************************//
//                                   Token                                    //
//****************************************************************************//

typedef struct s_token
{
	int		type;
	char	*lexeme;
}	t_token;

typedef struct s_token_list
{
	t_token				token;
	struct s_token_list	*next;
}	t_token_list;

//****************************************************************************//
//                                  COMMAND                                   //
//****************************************************************************//

typedef struct s_cmd
{
	int				type;
	t_token_list	*token_list;
}	t_cmd;

typedef struct s_cmd_list
{
	t_cmd				command;
	struct s_cmd_list	*next;
}	t_cmd_list;

//****************************************************************************//
//                                 Expression                                 //
//****************************************************************************//

typedef struct s_exp
{
	int				type;
	t_cmd_list		*cmd_list;
}	t_exp;

typedef struct s_exp_list
{
	t_exp				expression;
	struct s_exp_list	*next;
}	t_exp_list;

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

//****************************************************************************//
//                                  Lexing 1                                  //
//****************************************************************************//

// Coisas de manipulação de lista
t_token_list	*get_token_list(char *str);
void			token_add_to_list(t_token_list **token_list, char *lexeme, int type);
void			token_clear_list(t_token_list **token_list);
int				token_list_size(t_token_list *token_list);
void			token_back_one_node(t_token_list *token_list, t_token_list **node_to_back);
t_token_list	*token_get_sublist(t_token_list *token_list, int start, int list_length);

// Coisas de estados
int				token_state_is_final(int state);
int				token_state_requires_backtrack(int state);
int				token_get_next_state(int state, char character);
int				token_get_token_type(int state);

int				token_get_state_1(char character);
int				token_get_state_40(char character);
int				token_get_state_50(char character);
int				token_get_state_60(char character);
int				token_get_state_70(char character);
int				token_get_state_80(char character);
int				token_get_state_81(char character);
int				token_get_state_82(char character);

//****************************************************************************//
//                                  Lexing 2                                  //
//****************************************************************************//

// Manipulação de lista
t_exp_list		*get_exp_list(t_token_list *token_list);
// t_token_list	*exp_get_first_n_nodes(t_token_list *token_list, int length);
void			exp_add_to_list(t_exp_list **exp_list, t_cmd_list *cmd_token_lexeme, int token_type);
void			exp_clear_list(t_exp_list **exp_list);

// Coisas de estado
int				exp_get_next_state(int state, t_token_list *node);
int				exp_state_is_final(int state);
int				exp_get_token_type(int state);
int				exp_state_requires_backtrack(int state);

int				exp_get_state_1(t_token_list *node);
int				exp_get_state_60(t_token_list *node);

//****************************************************************************//
//                                  Lexing 3                                  //
//****************************************************************************//

t_cmd_list		*get_cmd_list(t_token_list *full_token_list, int start, int list_length);
void			cmd_clear_list(t_cmd_list **cmd_list);
void			cmd_add_to_list(t_cmd_list **cmd_list, t_token_list *token_lexeme, int token_type);


//****************************************************************************//
//                                   Utils                                    //
//****************************************************************************//

// Utils

int				is_metacharacter(char character);
int				is_an_expression(t_token_list *node);

#endif
