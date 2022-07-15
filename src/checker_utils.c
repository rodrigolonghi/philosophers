/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:52:00 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/15 01:23:14 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

static void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos && !data->need_stop)
	{
		if (data->philos[i].last_meal < now() - data->time_to_die)
		{
			print_status(data, now() - data->start_time, i + 1, "died");
			data->need_stop = TRUE;
		}
		i++;
	}
}

void	*check_end(void	*aux)
{
	int		i;
	int		count;
	t_data	*data;

	data = aux;
	while (!data->need_stop)
	{
		check_death(data);
		if (data->must_eat != 0)
		{
			i = 0;
			count = 0;
			while (i < data->num_of_philos)
			{
				if (data->philos[i].meals_consumed >= data->must_eat)
					count++;
				i++;
			}
			if (count == data->num_of_philos)
				data->need_stop = TRUE;
		}
	}
	return (NULL);
}
