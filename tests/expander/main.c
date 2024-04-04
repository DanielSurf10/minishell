/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/04/04 18:21:25 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*USER;

	for (int i = 0; envp[i]; i++)
	{
		if (ft_strncmp(envp[i], "USER=", 5) == 0)
			USER = ft_strdup(envp[i] + 5);
		printf("envp[%d]: %s\n", i, envp[i]);
	}
	printf("\n\nUSER: %s\n", USER);
}

char *get_envp_string(char *envp[])
{
	int i = 0;
	int len = 0;
	int offset = 0;
	char *envp_string;

	while (envp[i])
	{
		len += strlen(envp[i]) + 1;
		i++;
	}
	envp_string = (char *)malloc(len + 1);
	if (!envp_string)
		return NULL;
	while (envp[i])
	{
		strcpy(envp_string + offset, envp[i]);
		offset += strlen(envp[i]) + 1;
		i++;
	}
	return (envp_string);
}
