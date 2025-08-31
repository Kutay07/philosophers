/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:32:54 by kbatur            #+#    #+#             */
/*   Updated: 2025/09/01 01:13:38 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_list(pthread_mutex_t *m, int len)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&m[i]);
		i++;
	}
}

static void	destroy_mutexes(t_data *data)
{
	if (!data)
		return ;
	destroy_mutex_list(data->forks, data->philo_count);
	destroy_mutex_list(data->meal_lock, data->philo_count);
	pthread_mutex_destroy(&data->write_lock);
}

void	cleanup_data(t_data *data)
{
	if (!data)
		return ;
	set_the_light(data, RED_LIGHT);
	destroy_mutexes(data);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->meal_lock)
	{
		free(data->meal_lock);
		data->meal_lock = NULL;
	}
}
