/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:36:39 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/15 11:34:39 by leobarbo         ###   ########.fr       */
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

typedef struct s_aux_token_lits
{
	int		i;
	int		state;
	int		token_type;
	int		str_length;
	int		lexeme_length;
	char	*lexeme;
}	t_aux_token_list;

//****************************************************************************//
//                                 Functions                                  //
//****************************************************************************//

//****************************************************************************//
//                                  Lexing 1                                  //
//****************************************************************************//

// Coisas de manipulação de lista
t_token_list	*get_token_list(char *str);
void			token_add_to_list(t_token_list **tok_lst, char *lex, int type);
void			token_clear_list(t_token_list **token_list);
int				token_list_size(t_token_list *token_list);
void			token_back_one_node(t_token_list *tok_lst, t_token_list \
**node_to_back);
t_token_list	*tok_get_sublst(t_token_list *tok_lst, int start, int lst_len);

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
//                                   Utils                                    //
//****************************************************************************//

int				is_metacharacter(char character);
int				is_an_command_element(t_token_list *node);

#endif
