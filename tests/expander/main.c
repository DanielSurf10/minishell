/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:06:49 by leobarbo          #+#    #+#             */
/*   Updated: 2024/04/06 13:34:08 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*USER;

// 	for (int i = 0; envp[i]; i++)
// 	{
// 		if (ft_strncmp(envp[i], "USER=", 5) == 0)
// 			USER = ft_strdup(envp[i] + 5);
// 		printf("envp[%d]: %s\n", i, envp[i]);
// 	}
// 	printf("\n\nUSER: %s\n", USER);
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_Node
{
	char			*key;
	char 			*value;
	struct s_Node	*next;
}					s_Node;

s_Node	*createNode(char *key, char *value)
{
	s_Node	*newNode;

	newNode = (s_Node*)malloc(sizeof(s_Node));
	newNode->key = strdup(key);
	newNode->value = strdup(value);
	newNode->next = NULL;
	return newNode;
}

void	insertNode(s_Node **head, char *key, char *value)
{
	s_Node *newNode;
	s_Node *temp;

	newNode = createNode(key, value);
	if (*head == NULL)
		*head = newNode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
}

// void	printList(s_Node *head)
// {
// 	s_Node	*temp;

// 	temp = head;
// 	while (temp != NULL)
// 	{
// 		printf("Key: %s, Value: %s\n", temp->key, temp->value);
// 		temp = temp->next;
// 	}
// }

void	storeEnvpInLinkedList(char *envp[]) {
	s_Node *head;

	head = NULL;
	int i = 0;
	while (envp[i])
	{
		char *key = strtok(envp[i], "=");
		char *value = strtok(NULL, "=");
		insertNode(&head, key, value);
		i++;
	}
	printList(head);
}

int main(int argc, char *argv[], char *envp[]) {
	storeEnvpInLinkedList(envp);
	return 0;
}
