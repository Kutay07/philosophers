/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:00:00 by kutay             #+#    #+#             */
/*   Updated: 2025/08/31 14:44:36 by kutaydebian      ###   ########.fr       */
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

/* int	all_philosophers_finished_eating(t_data *data)
{
	int	i;
	int	finished_count;

	if (data->must_eat == -1)
		return (FAILURE);
	
	finished_count = 0;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock[i]);
		if (data->philos[i].meals_eaten >= data->must_eat)
			finished_count++;
		pthread_mutex_unlock(&data->meal_lock[i]);
		i++;
	}
	
	if (finished_count == data->philo_count)
		return (SUCCESS);
	return (FAILURE);
} */

void	monitor_philosophers(t_data *data)
{
	int	i;
	int all_satisfied;

	while (1)
	{
		i = 0;
		all_satisfied = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&data->meal_lock[i]);
			if (philosopher_died(data, i))
			{
				print_action(&data->philos[i], "died");
				/* Önce mevcut kilidi bırak, sonra tüm light değerlerini güncelle.
				 * Aksi halde set_the_light içinde aynı meal_lock[i] tekrar kilitlenmeye
				 * çalışılır ve Helgrind 'Attempt to re-lock' uyarısı verir. */
				pthread_mutex_unlock(&data->meal_lock[i]);
				set_the_light(data, RED_LIGHT);
				return ;
			}
			if (data->philos[i].satisfied)
				all_satisfied++;
			pthread_mutex_unlock(&data->meal_lock[i]);
			i++;
		}
		if (all_satisfied == data->philo_count)
		{
			set_the_light(data, RED_LIGHT);
			return ;
		}
		light_sleep(600, data);
	}
}
