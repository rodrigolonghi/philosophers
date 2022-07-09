/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:13:56 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/09 00:58:26 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philosophers.h>

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, &start_philosophy,
			&data->philos[i]);
		i++;
	}
}

static void	initiate_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i;
		if (i == data->num_of_philos - 1)
			data->philos[i].left_fork_id = 0;
		else
			data->philos[i].left_fork_id = i + 1;
		data->philos[i].right_fork_id = i;
		data->philos[i].meals_consumed = 0;
		data->philos[i].last_meal = now();
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		data->philos[i].data = data;
		i++;
	}
}

static void	initiate_data(char **argv, t_data *data)
{
	data->start_time = now();
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = 0;
	data->need_stop = FALSE;
	data->philos = malloc(data->num_of_philos * sizeof(t_philo));
	data->forks_mutex = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	initiate_philos(data);
}

static int	is_valid_arguments(char **argv)
{
	int	i;
	int	j;

	if (ft_atoi(argv[1]) == 0)
		return (FALSE);
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (FALSE);
		j = 0;
		while (argv[i][j] && ft_atoi(argv[i]) == 0)
		{
			if (!ft_isdigit(argv[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc < 5)
		printf("To few arguments!\n");
	else if (argc > 6)
		printf("To many arguments!\n");
	else if (!is_valid_arguments(argv))
		printf("Invalid arguments!\n");
	else
	{
		initiate_data(argv, &data);
		create_threads(&data);
		pthread_create(&data.checker, NULL, &check_end, &data);
		i = 0;
		while (i < data.num_of_philos)
		{
			pthread_join(data.philos[i].thread, NULL);
			i++;
		}
		pthread_join(data.checker, NULL);
		end_philosophy(&data);
	}
	return (0);
}
