/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:13:53 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/07/09 00:56:15 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE	0
# define TRUE	1

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	int			left_fork_id;
	int			right_fork_id;
	int			meals_consumed;
	t_data		*data;
	long int	last_meal;
	pthread_t	thread;
}	t_philo;

struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				need_stop;
	t_philo			*philos;
	long int		start_time;
	pthread_t		checker;
	pthread_mutex_t	*forks_mutex;
};

int			ft_atoi(char *str);
int			ft_isdigit(int c);
void		*start_philosophy(void *philo);
void		*check_end(void	*aux);
void		end_philosophy(t_data *data);
long int	now(void);

#endif
