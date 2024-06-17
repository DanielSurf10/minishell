/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:56:00 by leobarbo          #+#    #+#             */
/*   Updated: 2024/06/14 14:56:22 by leobarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_and(t_exec_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = exec_tree(tree->left, data);
	if (ret_code == 0)
		ret_code = exec_tree(tree->right, data);
	return (ret_code);
}

int	exec_or(t_exec_tree *tree, t_minishell *data)
{
	int	ret_code;

	ret_code = exec_tree(tree->left, data);
	if (ret_code != 0)
		ret_code = exec_tree(tree->right, data);
	return (ret_code);
}
