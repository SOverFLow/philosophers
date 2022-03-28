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

	data = *(t_data **)data_arg;
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

void	check_time_die(t_data *data)
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
			if (c_t - data->last_meal[i] > data->time_to_die)
			{
				pthread_mutex_lock(data->print_turn);
				printf("%ld: %d died\n", get_curent_time_msec(), i + 1);
				return ;
			}
			i++;
		}
	}
}

void	check_meal_count(t_data *data)
{
	int	i;
	int	num_lives;

	num_lives = 1;
	i = 0;
	while (num_lives)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->last_meal[i] < data->meal_count)
			{
				num_lives = 1;
				break ;
			}
			else
				num_lives = 0;
			i++;
		}
	}
}

void	check_is_die_or_meal_c(t_data *data)
{
	if (data->meal_count < 0)
		check_time_die(data);
	else
		check_meal_count(data);
}

int	main(int argc, char **argv)
{
	t_data		**data_args;
	t_data		*data;
	pthread_t	*threads;
	int			i;

	if (ft_break(argv, argc))
		return (0);
	data_args = init_data(argv + 1);
	data = data_args[0];
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philos);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->meal_count < 0)
			data->last_meal[i] = get_curent_time_msec();
		else
			data->last_meal[i] = 0;
		pthread_create(threads + i, NULL, routine, data_args + i);
		data->id = i;
		usleep(100);
		i++;
	}
	check_is_die_or_meal_c(data);
	return (0);
}
