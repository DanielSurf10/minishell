/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:02:56 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/11 18:38:37 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	exit_print_error_message(char *message)
{
	int			i;
	int			length;
	char		*line;
	const char	*to_print[] = {RED"ERROR: "RST"exit: ", message, NULL};

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
	ft_putendl_fd(line, STDERR_FILENO);
	free(line);
}

int	exit_arg_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			exit_print_error_message("numeric argument required");
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_minishell *data)
{
	int		ret_code;
	int		args_num;
	char	*ret_code_str;

	ret_code = 0;
	args_num = 0;
	while (argv[args_num])
		args_num++;
	if (args_num > 2)
	{
		exit_print_error_message("too many arguments");
		return (1);
	}
	if (args_num == 1)
	{
		ret_code_str = search_value(data->envp_list, "?");
		ret_code = ft_atoi(ret_code_str);
		free(ret_code_str);
	}
	else if (!exit_arg_valid(argv[1]))
		return (1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_signal = -1;
	return (ternary(args_num == 1, ret_code, ft_atoi(argv[1])));
}
