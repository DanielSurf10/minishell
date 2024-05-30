/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:33:47 by danbarbo          #+#    #+#             */
/*   Updated: 2024/05/24 16:34:02 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	ternary(int condition, int if_true, int if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}
