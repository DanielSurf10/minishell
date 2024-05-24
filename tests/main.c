/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/24 16:07:35 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

typedef struct test_list test_list;

struct test_list
{
	char		*to_expand;
	char		*expected;
	test_list	*next;
};

int	check_expand(t_node *list_envp, char *to_expand, char *expected)
{
	char	*expanded = expand(to_expand, list_envp);

	return (ft_strncmp(expected, expanded, -1) == 0);
}

void	add_test(test_list **expand_test_list, char *to_expand, char *expected)
{
	test_list	*new_node;
	test_list	*aux = *expand_test_list;

	while (aux && aux->next)
		aux = aux->next;

	new_node = malloc(sizeof(test_list));

	new_node->to_expand = ft_strdup(to_expand);
	new_node->expected = ft_strdup(expected);
	new_node->next = NULL;

	if (!aux)
		*expand_test_list = new_node;
	else
		aux->next = new_node;
}

int main(int argc, char *argv[], char *envp[])
{
	char		*str;
	char		*new_str;
	char		**new_envp;
	t_node		*list_envp;
	test_list	*aux;
	test_list	*expand_test_list = NULL;

	list_envp = store_to_list(envp);

	env_insert_node(&list_envp, ft_strdup("A"), ft_strdup("a\""));

	// Adiciona os testes
	add_test(&expand_test_list, "$USER", "danbarbo");
	add_test(&expand_test_list, "\"$USER\"", "danbarbo");
	add_test(&expand_test_list, "abc\"$USER\"abc", "abcdanbarboabc");
	add_test(&expand_test_list, "abc$USER abc", "abcdanbarbo abc");
	add_test(&expand_test_list, "abc $USER", "abc danbarbo");
	add_test(&expand_test_list, "\'$USER\'", "$USER");
	add_test(&expand_test_list, "abc \'$USER\'", "abc $USER");
	add_test(&expand_test_list, "\'$USER\' abc", "$USER abc");
	add_test(&expand_test_list, "abc\'$USER\"\'abc", "abc$USER\"abc");
	add_test(&expand_test_list, "batata", "batata");
	add_test(&expand_test_list, "\"a\"", "a");
	add_test(&expand_test_list, "\"abc\"", "abc");
	add_test(&expand_test_list, "abc\"a\"", "abca");
	add_test(&expand_test_list, "\"a\"abc", "aabc");
	add_test(&expand_test_list, "abc\"a\"abc", "abcaabc");
	add_test(&expand_test_list, "\"a\"abc\'a\'", "aabca");
	add_test(&expand_test_list, "\"a\"\'a\'", "aa");
	add_test(&expand_test_list, "\"a\'\"", "a'");
	add_test(&expand_test_list, "\"batata\'bata\'\"", "batata'bata'");
	add_test(&expand_test_list, "\"'$USER'\"", "'danbarbo'");
	add_test(&expand_test_list, "\"'\"$USER", "'danbarbo");
	add_test(&expand_test_list, "\"\"", "");
	add_test(&expand_test_list, "\"$A\"", "a\"");
	add_test(&expand_test_list, "'\"$A\"'", "\"$A\"");
	add_test(&expand_test_list, "\"'$A'\"", "'a\"'");
	add_test(&expand_test_list, "\"\"$A\"\"", "a\"");
	add_test(&expand_test_list, "''\"\"''", "");
	add_test(&expand_test_list, "''\"$A\"''", "a\"");

	// Testa
	aux = expand_test_list;
	while (aux)
	{
		printf("%11s - ", check_expand(list_envp, aux->to_expand, aux->expected) ? G"[ CORRETO ]"RST : RED"[ ERRADO! ]"RST);

		printf("%s - %s - %s\n", aux->to_expand, expand(aux->to_expand, list_envp), aux->expected);

		aux = aux->next;
	}

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
// $"'"
// $'"'
// $1"'"
