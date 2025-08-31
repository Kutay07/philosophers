/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:33:40 by kbatur            #+#    #+#             */
/*   Updated: 2025/09/01 01:14:15 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	light_sleep(philo->times.die);
	pthread_mutex_unlock(philo->first_fork);
	print_action(philo, "died");
}

static void	start_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock[philo->id - 1]);
	philo->times.last_meal_time = get_time();
	philo->meals_eaten++;
	if (philo->data->must_eat != -1
		&& philo->meals_eaten >= philo->data->must_eat)
		philo->satisfied = 1;
	pthread_mutex_unlock(&philo->data->meal_lock[philo->id - 1]);
	light_sleep(philo->times.eat);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
	print_action(philo, "is sleeping");
	light_sleep(philo->times.sleep);
	print_action(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->times.eat);
	while (is_this_the_light(philo->data, GREEN_LIGHT, philo->id - 1))
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		start_routine(philo);
	}
	return (NULL);
}
