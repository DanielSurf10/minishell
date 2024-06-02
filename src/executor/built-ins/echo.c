/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:00:09 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/02 15:29:05 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char *args[])
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && ft_strncmp(args[1], "-n", -1) == 0)
	{
		i++;
		n_flag = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
