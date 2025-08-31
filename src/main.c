/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatur <kbatur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:00:00 by kutay             #+#    #+#             */
/*   Updated: 2025/08/30 21:39:01 by kbatur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (FAILURE);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	init_simulation(char **argv, t_data *data)
{
	if (!init_mutexes(data))
	{
		cleanup_data(data);
		return (FAILURE);
	}
	if (init_philosophers(data, argv))
	{
		cleanup_data(data);
		return (FAILURE);
	}
	if (!create_threads(data))
	{
		cleanup_data(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	run_simulation(t_data *data)
{
	/* monitor_philosophers(data); */
	if (!join_threads(data))
	{
		cleanup_data(data);
		return (1);
	}
	cleanup_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != SUCCESS)
		return (FAILURE);
	if (parse_args(argc, argv, &data) != SUCCESS)
		return (FAILURE);
	if (init_simulation(argv, &data) != SUCCESS)
		return (FAILURE);
	return (run_simulation(&data));
}
