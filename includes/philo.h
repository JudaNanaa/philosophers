/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/07/02 12:29:53 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data {
	long nb_philo;
	long time_die;
	long time_eat;
	long time_sleep;
	int id;
	long nb_eat;
	int fork;
	char *nb_eat_args;
	int thinking;
	int finish;
	int die;
	unsigned long long int timesleeping;
	unsigned long long int timestart;
	unsigned long long int timefork;
	unsigned long long int timeeating;
	unsigned long long int timethinking;
	unsigned long long int timestamp;
	pthread_mutex_t *mutex;
	pthread_mutex_t *mutexprintf;
	pthread_mutex_t *mutexfork;
	pthread_mutex_t *mutexdie;
	pthread_mutex_t *mutexfinish;
	struct s_data *before;
	struct s_data *next;
	struct s_data *first;
	struct s_data *last;
	struct timeval curent_time;
} t_philo;

typedef struct s_mutex
{
	pthread_mutex_t *mutex;
	pthread_mutex_t *mutexprintf;
	pthread_mutex_t *mutexfork;
	pthread_mutex_t *mutexdie;
	pthread_mutex_t *mutexfinish;
}t_mutex;

extern int usleep (__useconds_t __useconds);

// Parsing
int ft_parse_args(int argc, char **argv, t_philo *data);


// Utils
long ft_atol(char *str);
int	ft_check_if_number(char **argv, int index);
void ft_init_mutex(t_mutex *mutex);
void ft_destroy_mutex(t_mutex *mutex);

// Struct
t_philo *ft_init_struct(t_philo *philo);
t_philo *ft_clear_philos(t_philo *philos);
int ft_check_if_die(t_philo *philos);

// Threads
int ft_creating_threads(t_philo *data, pthread_t *philos);
int ft_thread(t_philo *data);
int ft_eating(t_philo *philo, t_philo *left);
int ft_sleeping(t_philo *philo);
int ft_thinking(t_philo *philo);
int ft_change_or_check(t_philo *philo, t_philo *other, int cas);
int ft_die(t_philo *philo, t_philo *buff, int cas);

#endif // !FT_PHILO_H
