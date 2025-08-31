/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:45:52 by kutaydebian       #+#    #+#             */
/*   Updated: 2025/08/31 14:17:40 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, "has taken a fork");
	return (SUCCESS);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}

/* void	philosopher_eat(t_philo *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock[philo->id - 1]);
	philo->times.last_meal_ms = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock[philo->id - 1]);
	light_sleep(philo->times.eat, philo->data);
} */
