/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:51:22 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/06 20:16:54 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// static void	print_error_message(char *key_value)
// {
// 	int			length;
// 	char		*message_to_print;
// 	const char	*message[2] = {RED"ERROR: "RST"unset: '", \
// 								"': not a valid identifier"};

// 	length = ft_strlen(message[0]) + ft_strlen(key_value) \
// 						+ ft_strlen(message[1]) + 1;
// 	message_to_print = malloc(length);
// 	ft_strlcpy(message_to_print, message[0], length);
// 	ft_strlcat(message_to_print, key_value, length);
// 	ft_strlcat(message_to_print, message[1], length);
// 	ft_putendl_fd(message_to_print, STDERR_FILENO);
// 	free(message_to_print);
// }

int	builtin_unset(char **argv, t_envp_list **envp_list)
{
	int	i;
	int	ret_code;

	i = 0;
	ret_code = 0;
	while (argv[i])
	{
		if (key_is_valid(argv[i]))
			env_delete_value(envp_list, argv[i]);
		else
		{
			print_error_message(argv[i]);
			ret_code = 1;
		}
		i++;
	}
	return (ret_code);
}
