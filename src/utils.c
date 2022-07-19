/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:38:57 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/18 21:56:59 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

void	end_philosophy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		pthread_mutex_destroy(&data->std_output);
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philos[i].meals_consumed_mutex);
		i++;
	}
	free(data->philos);
	free(data->forks_mutex);
}

long int	now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((long int)(timeval.tv_sec * 1000 + timeval.tv_usec / 1000));
}

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
