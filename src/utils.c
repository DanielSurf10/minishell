
#include "expander.h"

void	clear_list(t_node *head)
{
	t_node	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

/*Função para deletar um nó da lista, caso a chave(key) exista*/
t_node	*env_delete_value(t_node *head, char *key)
{
	t_node	*temp;
	t_node	*prev;

	temp = head;
	prev = NULL;
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
		{
			if (prev == NULL)
				head = temp->next;
			else
				prev->next = temp->next;
			clear_list(temp);
			return (head);
		}
		prev = temp;
		temp = temp->next;
	}
	return (head);
}

/* Funcão para procurar se a chave(key) existe. Caso exista, vai apenas alterar o valor
da chave e retornar '1'*/
int	exist_in_list(t_node *head, char *key, char *value)
{
	t_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = strdup(value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	env_malloc(int size, char **dest)
{
	*dest = (char *)malloc(sizeof(char) * size);
	if (*dest == NULL)
		return ;
	*dest[size] = '\0';
}

void	ft_strcpy(char *dest, char *src, int idx)
{
	int i;

	i = 0;
	while (src[i] && i <= idx) // i <= idx para copiar até o idx
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
