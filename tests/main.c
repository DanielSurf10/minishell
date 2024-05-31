/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by daniel          #+#    #+#             */
/*   Updated: 2024/05/31 00:01:33 by daniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

typedef struct test_list test_list;

struct test_list
{
	char		*to_expand;
	char		*expected;
	test_list	*next;
};

int	check_expand(t_envp_list *list_envp, char *to_expand, char *expected)
{
	char	*expanded = expand_string(to_expand, list_envp);
	int		result = ft_strncmp(expected, expanded, -1) == 0;

	free(expanded);
	return (result);
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

void	clear_test_list(test_list **expand_test_list)
{
	test_list	*aux;
	test_list	*next;

	aux = *expand_test_list;
	while (aux)
	{
		next = aux->next;
		free(aux->to_expand);
		free(aux->expected);
		free(aux);
		aux = next;
	}
	*expand_test_list = NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	char		*str;
	char		*new_str;
	char		**new_envp;
	t_envp_list		*list_envp;
	test_list	*aux;
	test_list	*expand_test_list = NULL;

	list_envp = store_to_list(envp);

	env_insert_node(&list_envp, "A", "a\"");
	env_insert_node(&list_envp, "carol", "55");
	env_insert_node(&list_envp, "var", "o hello");
	env_insert_node(&list_envp, "var50", "abc      def");
	env_insert_node(&list_envp, "var50", "abc      def");

	printf(B"\n*************************************** RODANDO TESTES *************************************\n\n"RST);
	// Adiciona os testes
	add_test(&expand_test_list, "$USER", "daniel");
	add_test(&expand_test_list, "\"$USER\"", "daniel");
	add_test(&expand_test_list, "abc\"$USER\"abc", "abcdanielabc");
	add_test(&expand_test_list, "abc$USER abc", "abcdaniel abc");
	add_test(&expand_test_list, "abc $USER", "abc daniel");
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
	add_test(&expand_test_list, "\"'$USER'\"", "'daniel'");
	add_test(&expand_test_list, "\"'\"$USER", "'daniel");
	add_test(&expand_test_list, "\"\"", "");
	add_test(&expand_test_list, "\"$A\"", "a\"");
	add_test(&expand_test_list, "'\"$A\"'", "\"$A\"");
	add_test(&expand_test_list, "\"'$A'\"", "'a\"'");
	add_test(&expand_test_list, "\"\"$A\"\"", "a\"");
	add_test(&expand_test_list, "''\"\"''", "");
	add_test(&expand_test_list, "''\"$A\"''", "a\"");
	add_test(&expand_test_list, "$USER$carol", "daniel55");
	add_test(&expand_test_list, "$USER$var", "danielo hello");
	add_test(&expand_test_list, "oitudobem", "oitudobem");
	add_test(&expand_test_list, "$USERoi", "");
	add_test(&expand_test_list, "'$USER'", "$USER");
	add_test(&expand_test_list, "\"$USER\"", "daniel");
	add_test(&expand_test_list, "$$$", "");
	add_test(&expand_test_list, "$\"\" USER", " USER");
	add_test(&expand_test_list, "$\"\" USER \"\"", " USER ");


	// Teste
	aux = expand_test_list;
	while (aux)
	{
		printf("%11s - ", check_expand(list_envp, aux->to_expand, aux->expected) ? G"[ CORRETO ]"RST : RED"[ ERRADO! ]"RST);

		str = expand_string(aux->to_expand, list_envp);
		printf(C"Input: "RST "%-15s" "| " C"Retorno: "RST "%-15s" "| " C"Esperado: "RST "%s\n", aux->to_expand, str, aux->expected);
		free(str);

		aux = aux->next;
	}

	clear_test_list(&expand_test_list);
	clear_list(&list_envp);
	printf(B"\n********************************************************************************************\n\n"RST);
	return (0);
}




// $"" USER ""
// $"""                 " USER ""
// $"""""""""""" USER ""
// $"""" USER ""
// $""'' USER ""
// $'' USER ""
// $'''' USER ""
// $' ' '' USER ""
// $' '"" USER ""
// $"''" USER ""
// $'''' USER ""
// $  "''" USER ""
// $  """" USER ""
// $  "" USER
// "        $USER   "
// "carol"
// $"carol"
// "$carol"
// '$carol'
// $carolbia$
// $carolbia$ hi
// $carol$?bia$ hi
// $'carol'$'bia'$
// $"carol"$"bia"$
// $'carol''bia'
// $"carol""bia"
// ech$var
// $var50
// $adfasfsd
// $adfasfsd
// $%342342


// export carol=55
// export var="o hello"
// export var50="abc      def"
