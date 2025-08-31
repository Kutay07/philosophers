/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:33:29 by kbatur            #+#    #+#             */
/*   Updated: 2025/08/31 20:34:47 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philosopher_died(t_data *data, int i)
{
	size_t	current_time;
	size_t	time_since_meal;

	current_time = get_time_ms();
	time_since_meal = current_time - data->philos[i].times.last_meal_ms;
	if (time_since_meal > data->philos[i].times.die)
	{
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	philosopher_conditions(t_data *data, int i)
{
	int	all_satisfied;

	all_satisfied = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock[i]);
		if (philosopher_died(data, i))
		{
			print_action(&data->philos[i], "died");
			pthread_mutex_unlock(&data->meal_lock[i]);
			set_the_light(data, RED_LIGHT);
			return (-1);
		}
		if (data->philos[i].satisfied)
			all_satisfied++;
		pthread_mutex_unlock(&data->meal_lock[i]);
		i++;
	}
	return (all_satisfied);
}

void	monitor_philosophers(t_data *data)
{
	int	i;
	int	all_satisfied;

	while (1)
	{
		i = 0;
		all_satisfied = philosopher_conditions(data, i);
		if (all_satisfied == -1)
			return ;
		if (all_satisfied == data->philo_count)
		{
			set_the_light(data, RED_LIGHT);
			return ;
		}
		light_sleep(500);
	}
}
