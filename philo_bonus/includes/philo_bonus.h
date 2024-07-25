/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/07/25 19:09:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <bits/pthreadtypes.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_t				monitor;
	long					nb_philo;
	long long int			time_die;
	long					time_eat;
	long					time_sleep;
	int						id;
	long					nb_eat;
	int						die;
	unsigned long long int	timestart;
	unsigned long long int	timeeating;
	sem_t					*sem_printf;
	sem_t					*sem_fork;
	sem_t					*sem_taking_fork;
	sem_t					*sem_last_eat;
	sem_t					*sem_finish;
	sem_t					*sem_die;
	struct s_data			*before;
	struct s_data			*next;
	struct s_data			*first;
	struct s_data			*last;
}							t_philo;

typedef struct s_sema
{
	sem_t					*sem_fork;
	sem_t					*sem_print;
	sem_t					*sem_finish;
	sem_t					*sem_taking_fork;
	sem_t					*sem_last_eat;
	sem_t					*sem_die;
}							t_sema;

extern int					usleep(__useconds_t __useconds);

// Parsing
int							ft_parse_args(int argc, char **argv, t_philo *data);

// Utils
unsigned long long int		ft_time(t_philo *philo, int cas);
long						ft_atol(char *str);
int							ft_check_if_number(char **argv, int index);
int							ft_usleep(t_philo *philo,
								unsigned long long time_sleep);
int							ft_printf(char *str, t_philo *philo);

// Struct
t_philo						*ft_init_struct(t_philo *philo);
t_philo						*ft_clear_philos(t_philo *philos);
int							ft_check_if_die(t_philo *philos);

// Process
int							ft_process(t_philo *data);
int							ft_creating_process(t_philo *philo, pid_t *pid);
int							ft_thinking(t_philo *philo);
int							ft_eating(t_philo *philo);
int							ft_sleeping(t_philo *philo);
int							ft_taking_fork(t_philo *philo);
void						ft_drop_fork(t_philo *philo);
void						ft_one_philo(t_philo *philo);
void						ft_routine(t_philo *philo);
int							ft_semaphore_to_philo(t_sema *semaphore,
								t_philo *philo);
void						ft_semaphore_close(t_philo *philo);
void						ft_kill(pid_t *pid, int nb_philo);
int							ft_get_if_die(t_philo *philo);
void						*ft_monitoring(void *args);

unsigned long long int		ft_set_last_eat(t_philo *philo);

// Semaphores
int							ft_init_semaphores(t_sema *semaphores,
								t_philo *philo);

// Getter and Setter
void						ft_set_nb_eat(t_philo *philo);

#endif // !FT_PHILO_H
