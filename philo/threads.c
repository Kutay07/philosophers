/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:33:47 by kbatur            #+#    #+#             */
/*   Updated: 2025/09/01 01:14:18 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				philosopher_routine, &data->philos[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	light_sleep(size_t duration_ms)
{
	size_t	wait;
	size_t	current;

	wait = get_time();
	current = get_time();
	while (current - wait < duration_ms)
	{
		current = get_time();
		usleep(100);
	}
}
