/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/05/17 17:38:34 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int main(int argc, char *argv[], char *envp[]) {
	t_node	*list_envp;
	char	**new_envp;
	// char	*expanded;

	// list_envp = store_to_list(envp);

	// printList(list_envp);

	// env_insert_node(&list_envp, ft_strdup("teste"), ft_strdup("bomdia"));
	// env_insert_node(&list_envp, "teste", "boa tarde");

	// env_delete_value(&list_envp, "HOME");

	// new_envp = create_envp(list_envp);

	// expanded = expand("ola $teste", list_envp);		// ola bomdia

	// printList(list_envp);

	// printf("%s = %s\n", "SHELL", search_value(list_envp, "SHELL"));

	// free(search_value(list_envp, "SHELL"));

	// for (t_node *node = list_envp; node; node = node->next)
	// 	printf("%s = %s\n", node->key, search_value(list_envp, node->key));

	t_node	*head;
	char	*str;
	char	*new_str;

	head = store_to_list(envp);
	printList(head);
	str = ft_strdup("ola $USER, tudo bem?");
	new_str = expand(str, head);
	printf("%s\n", new_str);


	free_envp(new_envp);
	clear_list(&list_envp);

	return (0);
}
