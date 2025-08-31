/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:00:00 by kutay             #+#    #+#             */
/*   Updated: 2025/08/31 14:09:48 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
			return (print_usage("Thread birleştirme başarısız"));
		i++;
	}
	return (SUCCESS);
}

/* void	light_sleep(size_t duration_ms, t_data *data)
{
	size_t	start;
	size_t	current;

	start = get_time_ms();
	while (is_this_the_light(data, GREEN_LIGHT))
	{
		current = get_time_ms();
		if (current - start >= duration_ms)
			break ;
		usleep(50);
	}
} */

void	light_sleep(size_t duration_ms, t_data *data)
{
	size_t	wait;
	size_t	current;

	(void)data;
	wait = get_time_ms();
	current = get_time_ms();
	while (current - wait < duration_ms)
	{
		current = get_time_ms();
		usleep(100);
	}
}
