/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/07/08 20:40:16 by madamou          ###   ########.fr       */
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
# include <fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>


typedef struct s_data
{
	long					nb_philo;
	long					time_die;
	long					time_eat;
	long					time_sleep;
	int						id;
	long					nb_eat;
	char					*nb_eat_args;
	int						thinking;
	int						finish;
	int						die;
	unsigned long long int	timesleeping;
	unsigned long long int	timestart;
	unsigned long long int	timefork;
	unsigned long long int	timeeating;
	unsigned long long int	timethinking;
	unsigned long long int	timestamp;
	sem_t					*sem_printf;
	sem_t					*sem_fork;
	sem_t					*sem_die;
	struct s_data			*before;
	struct s_data			*next;
	struct s_data			*first;
	struct s_data			*last;
	struct timeval			curent_time;
}							t_philo;

typedef struct s_sema
{
	sem_t *sem_fork;
	sem_t *sem_print;
	sem_t *sem_die;
}							t_sema;

extern int					usleep(__useconds_t __useconds);

// Parsing
int							ft_parse_args(int argc, char **argv, t_philo *data);

// Utils
unsigned long long int		ft_time(t_philo *philo, int cas);
long						ft_atol(char *str);
int							ft_check_if_number(char **argv, int index);

// Struct
t_philo						*ft_init_struct(t_philo *philo);
t_philo						*ft_clear_philos(t_philo *philos);
int							ft_check_if_die(t_philo *philos);

// Process
int							ft_thread(t_philo *data);
int	ft_creating_process(t_philo *philo, pid_t *pid);


#endif // !FT_PHILO_H
