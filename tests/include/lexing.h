/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:36:39 by danbarbo          #+#    #+#             */
/*   Updated: 2024/04/04 16:38:21 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

// Includes

# include "minishell.h"

// Enums

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
	EXPRESSION
};

// Structs
// Token

typedef struct s_token
{
	int		type;
	char	*content;
}	t_token;

typedef struct s_token_list
{
	t_token				token;
	struct s_token_list	*next;
}	t_token_list;

// Expression

typedef struct s_exp
{
	int				type;
	t_token_list	*token_list;
}	t_exp;

typedef struct s_exp_list
{
	t_exp				expression;
	struct s_exp_list	*next;
}	t_exp_list;

// Functions
// Lexing 1

t_token_list	*get_token_list(char *str);
int				get_next_state(int state, char character);
int				state_is_final(int state);
int				get_token_type(int state);
int				state_requires_backtrack_one_char(int state);
void			clear_token_list(t_token_list **token_list);
void			add_token_to_list(t_token_list **token_list, char *lexeme, int type);

int				get_state_1(char character);
int				get_state_40(char character);
int				get_state_50(char character);
int				get_state_60(char character);
int				get_state_70(char character);
int				get_state_80(char character);
int				get_state_81(char character);
int				get_state_82(char character);

// Utils

int				is_metacharacter(char character);

// Lexing 2



#endif
