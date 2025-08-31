/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kutaydebian <kutaydebian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:00:00 by kutay             #+#    #+#             */
/*   Updated: 2025/08/31 13:57:50 by kutaydebian      ###   ########.fr       */
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
# define YELLOW_LIGHT -1
# define GREEN_LIGHT 0
# define RED_LIGHT 1
# define INT_MAX 2147483647
# define DIGIT_MAX 10

/* ************************************************************************** */
/*                               YAPI TANIMLARI                               */
/* ************************************************************************** */

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	last_meal_ms;
	size_t	start_time;
}	t_times;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id; //
	int					meals_eaten; //
	int					satisfied; //
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
	/* int					stop; */
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*meal_lock;
	// pthread_mutex_t		stop_lock;s
	t_philo				*philos;
}	t_data;

/* ************************************************************************** */
/*                            FONKSİYON PROTOTİPLERİ                         */
/* ************************************************************************** */

/* Temel yardımcı fonksiyonlar */
size_t		get_time_ms(void);
void		light_sleep(size_t duration_ms, t_data *data);
void		print_action(t_philo *philo, const char *action);
int			ft_atoi(const char *str);

/* Kurulum ve başlatma fonksiyonları */
int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data, char **argv);

/* Thread işlemleri */
void		*philosopher_routine(void *arg);
void		monitor_philosophers(t_data *data);
int			create_threads(t_data *data);
int			join_threads(t_data *data);

/* Temizlik ve hata yönetimi */
void		cleanup_data(t_data *data);

/* Doğrulama ve kontrol fonksiyonları */
int			check_args(int argc, char **argv);
int			all_philosophers_satisfied(t_data *data);
int			philosopher_died(t_data *data, int i);

int			print_usage(char *msg);
int			get_the_light(t_data *data, int i);
int			set_the_light(t_data *data, int light);
int			is_this_the_light(t_data *data, int light, int i);
int			take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		philosopher_eat(t_philo *philo);
void		destroy_mutex_list(pthread_mutex_t *m, int len);


#endif
