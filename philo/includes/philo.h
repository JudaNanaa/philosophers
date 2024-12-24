/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/12/21 00:56:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/pthreadtypes.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long					nb_philo;
	long					time_die;
	long					time_eat;
	long					time_sleep;
	int						id;
	long					nb_eat;
	int						die;
	unsigned long long int	timestart;
	unsigned long long int	timeeating;
	pthread_t				threads;
	pthread_mutex_t			*mutexprintf;
	pthread_mutex_t			my_fork;
	pthread_mutex_t			*next_fork;
	pthread_mutex_t			*mutexdie;
	pthread_mutex_t			mutex_nb_eat;
}							t_philo;

typedef struct s_mutex
{
	pthread_mutex_t			mutexprintf;
	pthread_mutex_t			mutexdie;
}							t_mutex;

extern int					usleep(__useconds_t __useconds);

// Parsing
int							ft_parse_args(int argc, char **argv, t_philo *data);

// Utils
unsigned long long int		ft_time(t_philo *philo, int cas);
long						ft_atol(char *str);
int							ft_check_if_number(char **argv, int index);
int							ft_printf(char *str, t_philo *philo);
int							ft_usleep(t_philo *philo,
								unsigned long long time_sleep);

// Struct
t_philo						*ft_init_struct(t_philo *philo);
t_philo						*ft_clear_philos(t_philo *philos);
int							ft_check_if_die(t_philo *philos);

// Threads
int							ft_creating_threads(t_philo *data);
int							ft_thread(t_philo *data);
int							ft_eating(t_philo *philo);
int							ft_sleeping(t_philo *philo);
int							ft_thinking(t_philo *philo);
void						*ft_routine(void *args);
int							ft_taking_fork(t_philo *philo,
								pthread_mutex_t *mutex);
void						ft_drop_fork(t_philo *philo);
void						ft_one_philo(t_philo *philo);

// Checker
int							ft_get_or_set_nb_eat(t_philo *philo, int cas);
unsigned long long int		ft_get_last_eat(t_philo *philo);
void						ft_main_thread(t_philo *philo);
int							ft_check_if_all_finish_eat(t_philo *philo);
void						ft_all_set_to_dead(t_philo *philo);

// getter and setter
unsigned long long int		ft_set_last_eat(t_philo *philo);
int							ft_get_if_die(t_philo *philo);

// Mutex
int							ft_init_mutex(t_mutex *mutex);

#endif // !FT_PHILO_H
