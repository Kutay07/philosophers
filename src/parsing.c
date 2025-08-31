/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:00:00 by kutay             #+#    #+#             */
/*   Updated: 2025/08/31 14:01:15 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_usage(char *msg)
{
	printf("Kullanım: ./philo filozof_sayısı ölüm_süresi yemek_süresi ");
	printf("uyku_süresi [her_filozofun_yemesi_gereken_yemek_sayısı]\n");
	printf("Tüm argümanlar pozitif tamsayı olmalıdır\n");
	if (msg)
	{
		printf("Hata: %s\n", msg);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (FAILURE);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || i > DIGIT_MAX)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	is_valid_argc(int argc)
{
	if (argc != 5 && argc != 6)
		return (FAILURE);
	return (SUCCESS);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	value;

	if (is_valid_argc(argc) != SUCCESS)
	{
		print_usage(NULL);
		return (FAILURE);
	}
	i = 1;
	while (i < argc)
	{
		if (is_valid_number(argv[i]) != SUCCESS)
			return (print_usage("Geçersiz argüman: sayı değil"));
		value = ft_atoi(argv[i]);
		if (value <= 0)
			return (print_usage("Geçersiz argüman: pozitif sayı olmalı"));
		if (i == 1 && value > 200)
			return (print_usage("Çok fazla filozof (maksimum 200)"));
		i++;
	}
	return (SUCCESS);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (init_data(data) != SUCCESS)
		return (FAILURE);
	data->philo_count = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (FAILURE);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
	{
		free(data->philos);
		return (FAILURE);
	}
	data->meal_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->meal_lock)
	{
		free(data->forks);
		free(data->philos);
		return (FAILURE);
	}
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (SUCCESS);
}
