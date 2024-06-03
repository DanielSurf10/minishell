/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:09:54 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/02 22:45:34 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	return (-1);
}

void	close_pipe(int *pipe_fd)
{
	pipe_fd[0] = close_fd(pipe_fd[0]);
	pipe_fd[1] = close_fd(pipe_fd[1]);
}

void	fd_list_add_fd(t_list **fd_list, int fd)
{
	int		*fd_ptr;
	t_list	*new;

	fd_ptr = malloc(sizeof(int));
	*fd_ptr = fd;
	new = ft_lstnew(fd_ptr);
	ft_lstadd_back(fd_list, new);
}

void	fd_list_close_clear(t_list **fd_list)
{
	t_list	*tmp;

	while (*fd_list)
	{
		close_fd(*((int *)(*fd_list)->content));
		tmp = *fd_list;
		*fd_list = (*fd_list)->next;
		free(tmp->content);
		free(tmp);
	}
}
