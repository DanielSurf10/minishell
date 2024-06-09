/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_macros.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:04:13 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/07 14:37:37 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	term_by_signal(int status)
{
	return (((signed char) ((status & 0x7f) + 1) >> 1) > 0);
}

int	term_normaly(int status)
{
	return (term_by_signal(status) == 0);
}

int	exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}

int	term_signal(int status)
{
	return (status & 0x7F);
}

int	get_return_value(int status)
{
	if (term_by_signal(status))
	{
		if (term_signal(status) == SIGQUIT)
			ft_putendl_fd(RED"QUIT"RST " (core dumped)", STDERR_FILENO);
		return (term_signal(status) + 128);
	}
	return (exit_status(status));
}
