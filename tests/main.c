/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/22 19:27:02 by danbarbo         ###   ########.fr       */
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

	env_insert_node(&list_envp, ft_strdup("A"), ft_strdup("a\""));
	// env_insert_node(&list_envp, ft_strdup("A"), ft_strdup("a\"\""));

	int		count = 1;
	printf("%2d - %s\n", count++, expand("$USER", list_envp));
	printf("%2d - %s\n", count++, expand("\"$USER\"", list_envp));
	printf("%2d - %s\n", count++, expand("abc\"$USER\"abc", list_envp));
	printf("%2d - %s\n", count++, expand("abc$USER abc", list_envp));
	printf("%2d - %s\n", count++, expand("abc $USER", list_envp));
	printf("%2d - %s\n", count++, expand("\'$USER\'", list_envp));
	printf("%2d - %s\n", count++, expand("abc \'$USER\'", list_envp));
	printf("%2d - %s\n", count++, expand("\'$USER\' abc", list_envp));
	printf("%2d - %s\n", count++, expand("abc\'$USER\"\'abc", list_envp));
	printf("%2d - %s\n", count++, expand("batata", list_envp));
	printf("%2d - %s\n", count++, expand("\"a\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"abc\"", list_envp));
	printf("%2d - %s\n", count++, expand("abc\"a\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"a\"abc", list_envp));
	printf("%2d - %s\n", count++, expand("abc\"a\"abc", list_envp));
	printf("%2d - %s\n", count++, expand("\"a\"abc\'a\'", list_envp));
	printf("%2d - %s\n", count++, expand("\"a\"\'a\'", list_envp));
	printf("%2d - %s\n", count++, expand("\"a\'\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"batata\'bata\'\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"'$USER'\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"'\"$USER", list_envp));
	printf("%2d - %s\n", count++, expand("\"\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"$A\"", list_envp));
	printf("%2d - %s\n", count++, expand("'\"$A\"'", list_envp));
	printf("%2d - %s\n", count++, expand("\"'$A'\"", list_envp));
	printf("%2d - %s\n", count++, expand("\"\"$A\"\"", list_envp));
	printf("%2d - %s\n", count++, expand("''\"\"''", list_envp));
	printf("%2d - %s\n", count++, expand("''\"$A\"''", list_envp));

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
// ""
// "$A"
// '"$A"'
// "'$A'"
// ""$A""
// ''""''
// ''"$A"''
