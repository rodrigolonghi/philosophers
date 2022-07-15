/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:08:23 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/14 22:39:08 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

void	print_status(t_data *data, long int timestamp, int philo_id, char *str)
{
	pthread_mutex_lock(&data->std_output);
	if (!data->need_stop)
		printf("%6ld %3d %s\n", timestamp, philo_id, str);
	pthread_mutex_unlock(&data->std_output);
}
