/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:32:13 by selhanda          #+#    #+#             */
/*   Updated: 2022/03/26 21:08:09 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data_arg)
{
	t_data			*data;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				id;

	data = (t_data *)data_arg;
	id = data->id;
	r_fork = data->forks + id;
	if (id < data->num_of_philos - 1)
		l_fork = data->forks + (id + 1);
	else
		l_fork = data->forks + 0;
	while (1)
	{
		philo_w_f_and_eat(data, id, r_fork, l_fork);
		pthread_mutex_lock(data->print_turn);
		printf("%ld: %d is sleeping\n", get_curent_time_msec(), id + 1);
		pthread_mutex_unlock(data->print_turn);
		get_exact_sleep_time(data->time_to_sleep);
		pthread_mutex_lock(data->print_turn);
		printf("%ld: %d is thinking\n", get_curent_time_msec(), id + 1);
		pthread_mutex_unlock(data->print_turn);
	}
	return (NULL);
}

int	check_time_die(t_data *data)
{
	int		i;
	time_t	c_t;

	usleep(1000);
	while (1)
	{
		c_t = get_curent_time_msec();
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->count == (data->num_of_philos * data->meal_count))
			{
				return (1);
			}
			if (c_t - data->last_meal[i] > data->time_to_die)
			{
				pthread_mutex_lock(data->print_turn);
				printf("%ld: %d died\n", get_curent_time_msec(), i + 1);
				return (1);
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	*threads;
	int			i;

	if (ft_break(argv, argc))
		return (0);
	data = init_data(argv + 1);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philos);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->last_meal[i] = get_curent_time_msec();
		pthread_create(threads + i, NULL, routine, data);
		data->id = i;
		usleep(100);
		i++;
	}
	if (check_time_die(data))
		return (0);
	return (0);
}
