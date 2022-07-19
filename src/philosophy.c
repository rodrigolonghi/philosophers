/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:56:43 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/18 22:31:31 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

static void	philo_think(t_philo *philo)
{
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"is thinking");
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->left_fork_id]);
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"has taken a fork");
	pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork_id]);
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"has taken a fork");
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = now();
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal = now();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->meals_consumed_mutex);
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->meals_consumed_mutex);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork_id]);
}

static void	just_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork_id]);
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	print_status(philo->data, now() - philo->data->start_time, philo->id + 1,
		"died");
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork_id]);
	pthread_mutex_lock(&philo->data->need_stop_mutex);
	philo->data->need_stop = TRUE;
	pthread_mutex_unlock(&philo->data->need_stop_mutex);
}

void	*start_philosophy(void *aux)
{
	t_philo	*philo;

	philo = aux;
	if (philo->data->num_of_philos == 1)
		just_one(philo);
	if (philo->id % 2 != 0)
		usleep(5000);
	while (!need_stop(philo->data))
	{
		if (!need_stop(philo->data))
			philo_eat(philo);
		if (!need_stop(philo->data))
			philo_sleep(philo);
		if (!need_stop(philo->data))
			philo_think(philo);
	}
	return (NULL);
}
