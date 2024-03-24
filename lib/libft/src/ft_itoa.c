/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:11:19 by danbarbo          #+#    #+#             */
/*   Updated: 2023/10/28 22:33:48 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_to_ascii_digit(int num)
{
	if (num < 0)
		num = -num;
	return (num + '0');
}

static int	number_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		digits;
	char	*num;

	sign = 0;
	digits = number_len(n);
	if (n < 0)
		sign = 1;
	num = (char *) malloc(digits + sign + 1);
	if (!num)
		return (NULL);
	num[digits + sign] = '\0';
	if (sign)
		num[0] = '-';
	while (digits > 0)
	{
		num[digits + sign - 1] = int_to_ascii_digit(n % 10);
		n /= 10;
		digits--;
	}
	return (num);
}
