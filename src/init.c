/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:33:16 by kbatur            #+#    #+#             */
/*   Updated: 2025/08/31 20:34:31 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(t_data *data)
{
	if (!data)
		return (FAILURE);
	memset(data, 0, sizeof(t_data));
	return (SUCCESS);
}

static int	init_mutex_list(pthread_mutex_t *m, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&m[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&m[i]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (FAILURE);
	if (!init_mutex_list(data->meal_lock, data->philo_count))
	{
		pthread_mutex_destroy(&data->write_lock);
		return (FAILURE);
	}
	if (!init_mutex_list(data->forks, data->philo_count))
	{
		pthread_mutex_destroy(&data->write_lock);
		destroy_mutex_list(data->meal_lock, data->philo_count);
		return (FAILURE);
	}
	set_the_light(data, GREEN_LIGHT);
	return (SUCCESS);
}

static void	assign_forks(t_data *data)
{
	int				i;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	i = 0;
	while (i < data->philo_count)
	{
		left_fork = &data->forks[i];
		right_fork = &data->forks[(i + 1) % data->philo_count];
		if (i % 2 == 0)
		{
			data->philos[i].first_fork = left_fork;
			data->philos[i].second_fork = right_fork;
		}
		else
		{
			data->philos[i].first_fork = right_fork;
			data->philos[i].second_fork = left_fork;
		}
		i++;
	}
}

int	init_philosophers(t_data *data, char **argv)
{
	int		i;
	size_t	start_time;

	start_time = get_time_ms();
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].satisfied = 0;
		data->philos[i].times.die = ft_atoi(argv[2]);
		data->philos[i].times.eat = ft_atoi(argv[3]);
		data->philos[i].times.sleep = ft_atoi(argv[4]);
		data->philos[i].times.start_time = start_time;
		data->philos[i].times.last_meal_ms = start_time;
		data->philos[i].data = data;
		i++;
	}
	assign_forks(data);
	return (SUCCESS);
}
