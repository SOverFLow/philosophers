/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:58:03 by selhanda          #+#    #+#             */
/*   Updated: 2022/03/27 17:01:52 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_curent_time_msec(void)
{
	struct timeval	c_t;
	time_t			time;

	gettimeofday(&c_t, NULL);
	time = c_t.tv_sec * 1000 + c_t.tv_usec / 1000;
	return (time);
}

void	get_exact_sleep_time(int msec)
{
	time_t	begin;

	begin = get_curent_time_msec();
	while (get_curent_time_msec() - begin < msec)
		usleep(500);
}

void	philo_w_f_and_eat(t_data *data, int id,
pthread_mutex_t *r_fork, pthread_mutex_t *l_fork)
{
	pthread_mutex_lock(r_fork);
	pthread_mutex_lock(data->print_turn);
	printf("%ld: %d has taken a fork\n", get_curent_time_msec(), id + 1);
	pthread_mutex_unlock(data->print_turn);
	pthread_mutex_lock(l_fork);
	pthread_mutex_lock(data->print_turn);
	if (data->meal_count < 0)
		data->last_meal[id] = get_curent_time_msec();
	printf("%ld: %d is eating\n", get_curent_time_msec(), id + 1);
	pthread_mutex_unlock(data->print_turn);
	get_exact_sleep_time(data->time_to_eat);
	pthread_mutex_unlock(r_fork);
	pthread_mutex_unlock(l_fork);
	if (data->meal_count > 0)
		data->last_meal[id] += 1;
}

void	init_data_int(t_data *data, char *argv[])
{
	data->num_of_philos = ft_atoi(argv[0]);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->meal_count = -1;
	if (argv[4])
		data->meal_count = ft_atoi(argv[4]);
}

t_data	**init_data(char *argv[])
{
	t_data	*data;
	t_data	**data_args;
	int		i;

	data = malloc(sizeof(t_data));
	init_data_int(data, argv);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	data->print_turn = malloc(sizeof(pthread_mutex_t));
	data->last_meal = malloc(sizeof(time_t) * data->num_of_philos);
	data_args = malloc(sizeof(t_data *) * data->num_of_philos);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(data->forks + i, NULL);
		data_args[i++] = data;
	}
	pthread_mutex_init(data->print_turn, NULL);
	return (data_args);
}
