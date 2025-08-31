/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:32:42 by kbatur            #+#    #+#             */
/*   Updated: 2025/09/01 01:00:53 by kutaydebian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <string.h>

# define SUCCESS 1
# define FAILURE 0
# define GREEN_LIGHT 0
# define RED_LIGHT 1
# define DIGIT_MAX 10

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	last_meal_time;
	size_t	start_time;
}	t_times;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	int					meals_eaten;
	int					satisfied;
	int					light;
	t_times				times;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					philo_count;
	int					must_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*meal_lock;
	t_philo				*philos;
}	t_data;

size_t		get_time(void);
void		cleanup_data(t_data *data);
void		light_sleep(size_t duration_ms);
void		*philosopher_routine(void *arg);
void		monitor_philosophers(t_data *data);
void		print_action(t_philo *philo, const char *action);
void		destroy_mutex_list(pthread_mutex_t *m, int len);
int			init_data(t_data *data);
int			ft_atoi(const char *str);
int			join_threads(t_data *data);
int			init_mutexes(t_data *data);
int			create_threads(t_data *data);
int			check_args(int argc, char **argv);
int			get_the_light(t_data *data, int i);
int			set_the_light(t_data *data, int light);
int			init_philosophers(t_data *data, char **argv);
int			parse_args(int argc, char **argv, t_data *data);
int			is_this_the_light(t_data *data, int light, int i);

#endif
