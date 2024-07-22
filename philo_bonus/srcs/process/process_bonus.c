/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 21:23:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_fork_create(pid_t *pid, t_philo *philo, int i, pthread_t *threads)
{
	int	id;
	int	die;

	*pid = fork();
	if (*pid == -1)
		return (-1);
	if (*pid == 0)
	{
		free(&*pid - i);
		free(threads);
 		ft_routine(philo);
		id = philo->id;
		die = philo->die;
		sem_close(philo->sem_last_eat);
		ft_semaphore_close(philo);
		ft_clear_philos(philo->first);
		if (die == 0)
			exit(0);
		else
			exit(id);
	}
	return (0);
}

void	ft_kill(t_checker *checker)
{
	int	i;

	i = 0;
	while (i < checker->nb_philo)
	{
		if (checker->pid[i] != 0)
			kill(checker->pid[i], SIGKILL);
		i++;
	}
}

int	ft_fork_wait(t_philo *philo, pthread_t *threads)
{
	int			nb_wait;
	t_checker	*checker;

	nb_wait = 0;
	while (nb_wait < philo->nb_philo)
	{
		if (pthread_join(threads[nb_wait], NULL) != 0)
			return (-1);
		nb_wait++;
	}
	checker = ft_checker_in_static(NULL, 2);
	sem_close(checker->sem_kill);
	free(checker->kill);
	free(checker);
	return (0);
}

int	ft_creating_process(t_philo *philo, pid_t *pid, pthread_t *threads)
{
	int		i;
	int		nb_philo;
	t_sema	semaphores;

	i = -1;
	nb_philo = philo->nb_philo;
	if (ft_init_semaphores(&semaphores) == -1)
		return (0);
	if (ft_semaphore_to_philo(&semaphores, philo) == -1)
		return (ft_semaphore_close(philo), 0);
	while (++i <= nb_philo - 1)
	{
		if (ft_fork_create(&pid[i], philo, i, threads) != 0)
			return (printf("Error creating forks %d\n", i), 0);
		philo = philo->before;
	}
	if (ft_create_threads(philo, threads, pid) == -1)
		return (ft_semaphore_close(philo), 0);
	if (ft_fork_wait(philo, threads) == -1)
		return (ft_semaphore_close(philo), 0);
	return (ft_semaphore_close(philo), 1);
}

int	ft_process(t_philo *philo)
{
	pid_t		*pid;
	pthread_t	*threads;

	pid = malloc(sizeof(pid_t) * philo->nb_philo);
	if (!pid)
		return (printf("Error malloc philos\n"), 0);
	threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!threads)
		return (free(pid), printf("Error malloc philos\n"), 0);
	if (ft_creating_process(philo, pid, threads) == 0)
		return (free(pid), free(threads), 0);
	free(pid);
	free(threads);
	return (1);
}
