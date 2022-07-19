/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:08:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/18 22:51:38 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

int	need_stop(t_data *data)
{
	int	result;

	result = FALSE;
	pthread_mutex_lock(&data->need_stop_mutex);
	if (data->need_stop == TRUE)
		result = TRUE;
	pthread_mutex_unlock(&data->need_stop_mutex);
	return (result);
}

void	print_status(t_data *data, long int timestamp, int philo_id, char *str)
{
	pthread_mutex_lock(&data->std_output);
	if (!need_stop(data))
		printf("%6ld %3d %s\n", timestamp, philo_id, str);
	pthread_mutex_unlock(&data->std_output);
}
