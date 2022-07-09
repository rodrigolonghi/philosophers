/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:38:57 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/08 22:46:20 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_find_start(char *s1, char *set)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (set[i] != '\0')
	{
		if (s1[start] == set[i])
		{
			start++;
			i = 0;
		}
		else
			i++;
	}
	return (start);
}

int	ft_atoi(char *str)
{
	int	signal;
	int	number;

	str += ft_find_start(str, " 	\t\n\r\v\f");
	signal = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	number = 0;
	while ((ft_isdigit(*str)))
	{
		number *= 10;
		number += signal * (*str - '0');
		str++;
	}
	return (number);
}
