/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/12/24 16:18:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/pthreadtypes.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef enum s_state
{
	CONTINUE,
	FINISH,
}					t_state;

typedef struct s_data
{
	long			nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			time_think;
	long			nb_must_eat;
	long long		time_start;
	t_state			state;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_printf;
}					t_data;

typedef struct s_philo
{
	pthread_mutex_t	my_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	pthread_t		thread;
	long			nb_eat;
	long long		last_meal;
	t_data			*data;
}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	mutexprintf;
	pthread_mutex_t	mutexdie;
}					t_mutex;

extern int			usleep(__useconds_t __useconds);

// Parsing
int					parse_args(int argc, char **argv, t_data *data);

// Utils
long long			get_time(void);
long				ft_atol(char *str);
int					check_if_number(char **argv, int index);
t_state				ft_printf(t_philo *philo, char *message);
t_state				ft_usleep(t_philo *philo, long long time_sleep);
t_state				set_simulation_finish(t_philo *philo);

// Struct
t_philo				*init_philo(t_data *data);

// Threads
int					ft_thread(t_philo *philos, t_data *data);
t_state				eating(t_philo *philo);
t_state				sleeping(t_philo *philo);
t_state				thinking(t_philo *philo);
void				*routine(void *args);
int					taking_one_fork(t_philo *philo, pthread_mutex_t *mutex);
void				drop_fork(t_philo *philo);
void				one_philo(t_philo *philo);

// Checker
t_state				get_simulation_state(t_philo *philo);
t_state				set_simulation_finish(t_philo *philo);
t_state				check_if_die(t_philo *philos);

// Mutex
int					init_mutex(t_mutex *mutex);

#endif // !FT_PHILO_H
