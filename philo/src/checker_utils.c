/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:52:00 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/09 00:57:49 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

void	*check_end(void	*aux)
{
	int		i;
	int		count;
	t_data	*data;

	data = aux;
	if (data->must_eat != 0 && !data->need_stop)
	{
		while (!data->need_stop)
		{
			i = 0;
			count = 0;
			while (i < data->num_of_philos)
			{
				if (data->philos[i].meals_consumed >= data->must_eat)
					count++;
				i++;
			}
			if (count == data->must_eat)
				data->need_stop = TRUE;
		}
	}
	return (NULL);
}
