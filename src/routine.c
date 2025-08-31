/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:30:44 by kutaydebian       #+#    #+#             */
/*   Updated: 2025/08/31 14:34:41 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	light_sleep(philo->times.die, philo->data);
	pthread_mutex_unlock(philo->first_fork);
	print_action(philo, "died");
	
}

// static int	am_alive(t_philo *philo)
// {
// 	size_t	current_time;
// 	size_t	time_since_meal;

// 	current_time = get_time_ms();
// 	time_since_meal = current_time - philo->times.last_meal_ms;
// 	if (time_since_meal > philo->times.die)
// 		return (FAILURE);
// 	return (SUCCESS);
// }

static void	start_routine(t_philo *philo)
{
	int		has_forks;

	has_forks = 0;
	while (is_this_the_light(philo->data, GREEN_LIGHT, philo->id - 1))
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		if (!take_forks(philo))
			break ;
		has_forks = 1;
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->data->meal_lock[philo->id - 1]);
		philo->times.last_meal_ms = get_time_ms();
		philo->meals_eaten++;
		if (philo->data->must_eat != -1 && philo->meals_eaten >= philo->data->must_eat)
			philo->satisfied = 1;
		pthread_mutex_unlock(&philo->data->meal_lock[philo->id - 1]);
		light_sleep(philo->times.eat, philo->data);
		release_forks(philo);
		has_forks = 0;
		print_action(philo, "is sleeping");
		light_sleep(philo->times.sleep, philo->data);
		print_action(philo, "is thinking");
	}
	if (has_forks)
		release_forks(philo);
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
	start_routine(philo);
	return (NULL);
}
