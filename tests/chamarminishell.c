/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chamarminishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:28:45 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/18 16:31:19 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	char *arg[] = {"./minishell", NULL};
	execve("./minishell", arg, NULL);
}
