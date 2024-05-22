/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/21 16:19:03 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	*new_str;
	char	**new_envp;
	t_node	*list_envp;

	list_envp = store_to_list(envp);

	// printf("%s\n", expand("$USER", list_envp));
	// printf("%s\n", expand("\"$USER\"", list_envp));
	// printf("%s\n", expand("abc\"$USER\"abc", list_envp));
	// printf("%s\n", expand("abc$USER abc", list_envp));
	// printf("%s\n", expand("abc $USER", list_envp));
	// printf("%s\n", expand("\'$USER\'", list_envp));
	// printf("%s\n", expand("abc \'$USER\'", list_envp));
	// printf("%s\n", expand("\'$USER\' abc", list_envp));
	// printf("%s\n", expand("abc\'$USER\"\'abc", list_envp));
	// printf("%s\n", expand("batata", list_envp));
	// printf("%s\n", expand("\"a\"", list_envp));
	// printf("%s\n", expand("\"abc\"", list_envp));
	// printf("%s\n", expand("abc\"a\"", list_envp));
	// printf("%s\n", expand("\"a\"abc", list_envp));
	// printf("%s\n", expand("abc\"a\"abc", list_envp));
	// printf("%s\n", expand("\"a\"abc\'a\'", list_envp));
	// printf("%s\n", expand("\"a\"\'a\'", list_envp));
	// printf("%s\n", expand("\"a\'\"", list_envp));
	// printf("%s\n", expand("\"batata\'bata\'\"", list_envp));

	char	*line;

	do {
		line = readline("string: ");
		add_history(line);
		if (line)
			printf("%s\n", expand(line, list_envp));
	} while (line);

	// free(new_str);
	clear_list(&list_envp);

	return (0);
}

// $USER -> danbarbo
// oi $USER -> oi danbarbo
// oi $1 tudo bem-> oi  tudo bem
// $$ ->
// oi $$ tudo bem -> oi  tudo bem
// oi $1USER tudo bem -> oi  tudo bem
// oi $ a -> oi  a
// oi $$ a -> oi  a
// oi $$$USER -> oi danbarbo
