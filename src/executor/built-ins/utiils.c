/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:57:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/31 16:06:28 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	verify_built_in(char *command)
{
	int			i;
	const char	*built_ins[] = {"echo", "cd", "pwd", "export", "unset", "env", \
								"exit"};

	i = 0;
	while (command && i < 7)
	{
		if (ft_strncmp(command, built_ins[i], -1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_built_in(t_exec_tree *tree)
{
	int	command_is_built_in;

	if (!tree)
		return (0);
	command_is_built_in = 0;
	if (tree->type == COMMAND && tree->command)
		command_is_built_in = verify_built_in(tree->command->token.lexeme);
	else
		command_is_built_in = is_built_in(tree->right);
	return (command_is_built_in);
}
