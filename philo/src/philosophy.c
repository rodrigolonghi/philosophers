/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:56:43 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/09 01:01:40 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

static void	philo_think(t_philo *philo)
{
	printf("%6ld %3d is thinking\n", now() - philo->data->start_time,
		philo->id + 1);
}

static void	philo_sleep(t_philo *philo)
{
	printf("%6ld %3d is sleeping\n", now() - philo->data->start_time,
		philo->id + 1);
	usleep(philo->data->time_to_sleep);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->left_fork_id]);
	pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork_id]);
	printf("%6ld %3d has taken a fork\n", now() - philo->data->start_time,
		philo->id + 1);
	printf("%6ld %3d has taken a fork\n", now() - philo->data->start_time,
		philo->id + 1);
	printf("%6ld %3d is eating\n", now() - philo->data->start_time,
		philo->id + 1);
	usleep(philo->data->time_to_eat);
	philo->last_meal = now();
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork_id]);
}

static void	just_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork_id]);
	printf("%6ld %3d has taken a fork\n", now() - philo->data->start_time,
		philo->id + 1);
	usleep(philo->data->time_to_die * 1000);
	printf("%6ld %3d died\n", now() - philo->data->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork_id]);
	philo->data->need_stop = TRUE;
}

void	*start_philosophy(void *aux)
{
	t_philo	*philo;

	philo = aux;
	if (philo->data->num_of_philos == 1)
		just_one(philo);
	while (!philo->data->need_stop)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
