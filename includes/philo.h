/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/06/29 20:01:14 by madamou          ###   ########.fr       */
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
	pthread_mutex_t mutex;
	struct s_data *before;
	struct s_data *next;
	struct s_data *first;
	struct s_data *last;
} t_philo;

// Parsing
int ft_parse_args(int argc, char **argv, t_philo *data);


// Utils
long ft_atol(char *str);
int	ft_check_if_number(char **argv, int index);

// Init
t_philo *ft_init_struct(t_philo *philo);

// Threads
int ft_creating_threads(t_philo *data, pthread_t *philos);
int ft_thread(t_philo *data);

#endif // !FT_PHILO_H
