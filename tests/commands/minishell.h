/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:57 by danbarbo          #+#    #+#             */
/*   Updated: 2024/03/25 21:49:52 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include <readline/history.h>
# include <readline/readline.h>

# include "libft.h"

typedef struct s_command
{
	int		pid;
	int		input;
	int		output;
	int		arguments_count;
	char	*command;
	char	*expanded_command;
	char	**args;
}	t_command;

#endif
