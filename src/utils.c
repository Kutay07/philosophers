/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:33:54 by kbatur            #+#    #+#             */
/*   Updated: 2025/08/31 20:33:55 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (str[i] - '0') + (ret * 10);
		i++;
	}
	return (ret * sign);
}

void	print_action(t_philo *philo, const char *action)
{
	int			timestamp;
	static int	die_flag;

	pthread_mutex_lock(&philo->data->write_lock);
	if (die_flag == 0)
	{
		timestamp = get_time_ms() - philo->times.start_time;
		printf("%d\t %d %s\n", timestamp, philo->id, action);
	}
	if (action[0] == 'd')
		die_flag = 1;
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	get_the_light(t_data *data, int i)
{
	int	light;

	pthread_mutex_lock(&data->meal_lock[i]);
	light = data->philos[i].light;
	pthread_mutex_unlock(&data->meal_lock[i]);
	return (light);
}

int	set_the_light(t_data *data, int light)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock[i]);
		data->philos[i].light = light;
		pthread_mutex_unlock(&data->meal_lock[i]);
		i++;
	}
	return (SUCCESS);
}

int	is_this_the_light(t_data *data, int light, int i)
{
	if (get_the_light(data, i) == light)
		return (SUCCESS);
	return (FAILURE);
}
