/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:45:52 by kutaydebian       #+#    #+#             */
/*   Updated: 2025/08/30 21:49:05 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_forks(t_philo *philo)
{
/* 	if (is_this_the_light(philo->data, RED_LIGHT))
		return (1); */
	pthread_mutex_lock(philo->first_fork);
/* 	if (is_this_the_light(philo->data, RED_LIGHT))
	{
		pthread_mutex_unlock(philo->first_fork);
		return (1);
	} */
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
/* 	if (is_this_the_light(philo->data, RED_LIGHT))
	{
		pthread_mutex_unlock(philo->second_fork);
		pthread_mutex_unlock(philo->first_fork);
		return (1);
	} */
	print_action(philo, "has taken a fork");
	return (0);
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
