/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selhanda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:36:12 by selhanda          #+#    #+#             */
/*   Updated: 2022/03/27 17:37:11 by selhanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

static int	is_num(char *str)
{
	if (! str || ! *str)
		return (0);
	else if (my_isdigit(*str))
		str++;
	else if ((*str == '-' || *str == '+') && *(str + 1))
		str++;
	else
		return (0);
	while (*str)
	{
		if (! my_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	norm(char *str)
{
	if (str)
	{
		if (ft_atoi(str) <= 0)
		{
			printf("arg value error\n");
			return (1);
		}
	}
	return (0);
}

int	ft_break(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		if (!is_num(argv[i]))
		{
			printf("arg value error\n");
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0)
	{
		printf("arg value error\n");
		return (1);
	}
	if (ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
	{
		printf("arg value error\n");
		return (1);
	}
	return (norm(argv[5]));
}
