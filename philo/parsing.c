/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:33:35 by kbatur            #+#    #+#             */
/*   Updated: 2025/09/01 01:14:12 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_usage(int exit)
{
	printf("Usage: ./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (exit);
}

static int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (FAILURE);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || i > DIGIT_MAX)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	is_valid_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return (FAILURE);
	return (SUCCESS);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	value;

	if (is_valid_argc(argc) != SUCCESS)
		(print_usage(FAILURE));
	i = 1;
	while (i < argc)
	{
		if (is_valid_number(argv[i]) != SUCCESS)
			return (print_usage(FAILURE));
		value = ft_atoi(argv[i]);
		if (value <= 0)
			return (print_usage(FAILURE));
		if (i == 1 && value > 200)
			return (print_usage(FAILURE));
		i++;
	}
	return (SUCCESS);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (init_data(data) != SUCCESS)
		return (FAILURE);
	data->philo_count = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (FAILURE);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
	{
		free(data->philos);
		return (FAILURE);
	}
	data->meal_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->meal_lock)
	{
		free(data->forks);
		free(data->philos);
		return (FAILURE);
	}
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (SUCCESS);
}
