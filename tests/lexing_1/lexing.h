/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:36:39 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/30 22:06:21 by danbarbo         ###   ########.fr       */
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
};

// Structs

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

// Functions

int		get_next_state(int state, char character);
int		state_is_final(int state);
int		get_token_type(int state);
int		state_requires_backtrack_one_char(int state);
void	clear_token_list(t_token_list **token_list);
void	add_token_to_list(t_token_list **token_list, char *lexeme, int type);

int		get_state_1(char character);
int		get_state_40(char character);
int		get_state_50(char character);
int		get_state_60(char character);
int		get_state_70(char character);
int		get_state_80(char character);
int		get_state_81(char character);
int		get_state_82(char character);

// Utils

int		is_metacharacter(char character);

#endif
