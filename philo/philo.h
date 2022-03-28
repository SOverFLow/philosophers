/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:05:20 by selhanda          #+#    #+#             */
/*   Updated: 2022/03/27 17:05:26 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_philos;
	int				meal_count;
	time_t			*last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_turn;
}					t_data;

int		ft_atoi(const char *str);
int		ft_break(char **argv, int argc);
time_t	get_curent_time_msec(void);
void	get_exact_sleep_time(int msec);
void	philo_w_f_and_eat(t_data *data, int id,
			pthread_mutex_t	*r_fork, pthread_mutex_t *l_fork);
void	init_data_int(t_data *data, char *argv[]);
t_data	**init_data(char *argv[]);
void	*routine(void *data_arg);
void	check_time_die(t_data *data);
void	check_meal_count(t_data *data);
void	check_is_die_or_meal_c(t_data *data);

#endif
