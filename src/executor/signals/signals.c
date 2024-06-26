/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:22:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/14 15:54:21 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	sig_handler_heredoc(int signal __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
	g_signal = SIGINT;
}

void	sig_handler_sigint(int signal __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	g_signal = SIGINT;
}

void	sig_handler_redo_readline(int signal __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
