/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:03 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 20:47:38 by madamou          ###   ########.fr       */
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
	
	pthread_t				*monitor;
	long					nb_philo;
	unsigned long long int	time_die;
	long					time_eat;
	long					time_sleep;
	int						id;
	long					nb_eat;
	char					*nb;
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
	sem_t					*sem_taking_fork;
	sem_t					*sem_last_eat;
	sem_t					*sem_die;
	struct s_data			*before;
	struct s_data			*next;
	struct s_data			*first;
	struct s_data			*last;
	struct timeval			curent_time;
}							t_philo;

typedef struct s_sema
{
	sem_t					*sem_fork;
	sem_t					*sem_print;
	sem_t					*sem_die;
	sem_t					*sem_taking_fork;
	sem_t					*sem_last_eat;
}							t_sema;

typedef struct s_checker
{
	pid_t					*pid;
	long					nb_philo;
	int						i;
	t_philo					*philo;
	int						*kill;
	sem_t					*sem_kill;
	struct s_checker		*first;

}							t_checker;

extern int					usleep(__useconds_t __useconds);

// Parsing
int							ft_parse_args(int argc, char **argv, t_philo *data);

// Utils
unsigned long long int		ft_time(t_philo *philo, int cas);
long						ft_atol(char *str);
int							ft_check_if_number(char **argv, int index);
int							ft_usleep(t_philo *philo,
								unsigned long long time_sleep);
int							ft_printf(char *str, unsigned long long int time,
								t_philo *philo);
char						*ft_itoa(int n);

// Struct
t_philo						*ft_init_struct(t_philo *philo);
t_philo						*ft_clear_philos(t_philo *philos);
int							ft_check_if_die(t_philo *philos);

// Process
int							ft_process(t_philo *data);
int							ft_creating_process(t_philo *philo, pid_t *pid,
								pthread_t *threads);
int							ft_thinking(t_philo *philo);
int							ft_eating(t_philo *philo);
int							ft_sleeping(t_philo *philo);
int							ft_taking_fork(t_philo *philo);
void						ft_drop_fork(t_philo *philo);
int							ft_die(t_philo *philo);
void						ft_one_philo(t_philo *philo);
void						ft_routine(t_philo *philo);
int							ft_semaphore_to_philo(t_sema *semaphore,
								t_philo *philo);
int							ft_init_semaphores(t_sema *semaphores);
void						ft_semaphore_close(t_philo *philo);
void						*ft_routine_threads(void *args);
t_checker					*ft_checker_in_static(t_checker *checker, int cas);
t_checker					*ft_init_checker(t_philo *philo, pid_t *pid, int i);
void						ft_kill(t_checker *checker);
int							ft_create_threads(t_philo *philo,
								pthread_t *threads, pid_t *pid);
int	ft_get_or_set_nb_eat(t_philo *philo, int cas);
int	ft_get_if_die(t_philo *philo);
void *ft_monitoring(void *args);
int ft_init_semaphores2(t_philo *philo);
unsigned long long int	ft_set_last_eat(t_philo *philo);

						

#endif // !FT_PHILO_H
