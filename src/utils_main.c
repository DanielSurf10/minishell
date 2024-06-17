/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:24:24 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/14 15:02:55 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "expander.h"
#include "executor.h"
#include "minishell.h"

static void	print_m(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
}

void	print_menu(void)
{
	print_m(ORANGE"═══════════════════════════");
	print_m(ORANGE"════════════════════════════════════════\n");
	print_m(BLUE"░░░╗   ░░░╗░░╗░░░╗   ░░╗░░╗");
	print_m(BLUE"░░░░░░░╗░░╗  ░░╗░░░░░░░╗░░╗     ░░╗     \n");
	print_m(BLUE"░░░░╗ ░░░░║░░║░░░░╗  ░░║░░║");
	print_m(BLUE"░░╔════╝░░║  ░░║░░╔════╝░░║     ░░║     \n");
	print_m(BLUE"░░╔░░░░╔░░║░░║░░╔░░╗ ░░║░░║");
	print_m(BLUE"░░░░░░░╗░░░░░░░║░░░░░╗  ░░║     ░░║     \n");
	print_m(BLUE"░░║╚░░╔╝░░║░░║░░║╚░░╗░░║░░║");
	print_m(BLUE"╚════░░║░░╔══░░║░░╔══╝  ░░║     ░░║     \n");
	print_m(BLUE"░░║ ╚═╝ ░░║░░║░░║ ╚░░░░║░░║");
	print_m(BLUE"░░░░░░░║░░║  ░░║░░░░░░░╗░░░░░░░╗░░░░░░░╗\n");
	print_m(BLUE"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝");
	print_m(BLUE"╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	print_m(ORANGE"═══════════════════════════");
	print_m(ORANGE"══════════════════════════by_barbos═════\n");
	print_m(RST);
}

char	*get_line_to_readline(t_envp_list *env_list)
{
	int			i;
	int			length;
	char		*line;
	const char	*vars[2] = {search_value(env_list, "USER"), \
							search_value(env_list, "PWD")};
	const char	*to_print[] = {ORANGE, vars[0], RST, \
				CYAN, vars[1], RST, ": ", NULL};

	i = 0;
	length = 0;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	free((char *)vars[0]);
	free((char *)vars[1]);
	return (line);
}
