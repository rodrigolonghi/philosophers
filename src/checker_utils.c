/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:52:00 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/18 22:29:54 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

static void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos && !need_stop(data))
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mutex);
		if (data->philos[i].last_meal < now() - data->time_to_die)
		{
			print_status(data, now() - data->start_time, i + 1, "died");
			pthread_mutex_lock(&data->need_stop_mutex);
			data->need_stop = TRUE;
			pthread_mutex_unlock(&data->need_stop_mutex);
		}
		pthread_mutex_unlock(&data->philos[i].last_meal_mutex);
		i++;
	}
}

static void	check_meals_consumed(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].meals_consumed_mutex);
		if (data->philos[i].meals_consumed >= data->must_eat)
			count++;
		pthread_mutex_unlock(&data->philos[i].meals_consumed_mutex);
		i++;
	}
	if (count == data->num_of_philos)
	{
		pthread_mutex_lock(&data->need_stop_mutex);
		data->need_stop = TRUE;
		pthread_mutex_unlock(&data->need_stop_mutex);
	}
}

void	*check_end(void	*aux)
{
	t_data	*data;

	data = aux;
	while (!need_stop(data))
	{
		check_death(data);
		if (data->must_eat != 0)
			check_meals_consumed(data);
	}
	return (NULL);
}
