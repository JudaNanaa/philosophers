/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/10 01:36:22 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <semaphore.h>
#include <stdio.h>

void ft_semaphore_to_philo(t_sema *semaphore, t_philo *philo)
{
	while (philo)
	{
		philo->sem_fork = semaphore->sem_fork;
		philo->sem_die = semaphore->sem_die;
		philo->sem_printf = semaphore->sem_print;
		philo = philo->next;
	}
}

void ft_routine(t_philo *philo)
{
	sem_wait(philo->sem_printf);
	sem_post(philo->sem_printf);
	if (ft_time(philo, 1) == 0)
		return ;
	// while (1)
	// {
	// 	if (ft_thinking(philo) == 0)
	// 		return ;
	// 	if (ft_eating(philo) == 0)
	// 		return ;
	// 	if (ft_sleeping(philo) == 0)
	// 		return ;
	// }
	printf("oui je suis le philo numero %d", philo->id);
}

int ft_init_semaphores(t_sema *semaphores, t_philo *philo)
{
	semaphores->sem_fork = sem_open("fork", O_CREAT, 0600, philo->nb_philo);
	if (semaphores->sem_fork == SEM_FAILED)
		return (printf("Error open semaphore fork\n"), -1);
	semaphores->sem_die = sem_open("die", O_CREAT, 0600, 1);
	if (semaphores->sem_die == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		return (printf("Error open semaphore die\n"), -1);
	}
	semaphores->sem_print = sem_open("print", O_CREAT, 0600, 1);
	if (semaphores->sem_print == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		sem_close(semaphores->sem_die);
		return (printf("Error open semaphore print\n"), -1);
	}
	return (0);
}

void ft_semaphore_close(t_philo *philo)
{
	if (sem_close(philo->sem_die) == -1)
		printf("Error when close semaphore die\n");
	if (sem_close(philo->sem_fork)== -1)
		printf("Error when close semaphore fork\n");
	if (sem_close(philo->sem_printf)== -1)
		printf("Error when close semaphore printf");
}

int ft_fork_create(pid_t *pid, t_philo *philo, int i)
{
	*pid = fork();
	if (*pid == -1)
		return (-1);
	if (*pid == 0)
	{
		free(&*pid - i);
		ft_routine(philo);
		ft_semaphore_close(philo);
		ft_clear_philos(philo->first);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int ft_fork_wait(pid_t pid)
{
	return (waitpid(pid, NULL, 0));
}

int	ft_creating_process(t_philo *philo, pid_t *pid)
{
	int		i;
	int		nb_philo;
	t_sema semaphores;

	i = -1;
	nb_philo = philo->nb_philo;
	if (ft_init_semaphores(&semaphores, philo) == -1)
		return (0);
	ft_semaphore_to_philo(&semaphores, philo);
	sem_wait(semaphores.sem_print);
	while (++i <= nb_philo - 1)
	{
		if (ft_fork_create(&pid[i], philo, i) != 0)
			return (printf("Error creating forks %d\n", i), 0);
		philo = philo->before;
	}
	sem_post(semaphores.sem_print);
	i = -1;
	while (++i <= nb_philo - 1)
	{
		if (ft_fork_wait(pid[i]) == -1)
			return (printf("Error waiting process %d\n", i), 0);
	}
	return (ft_semaphore_close(philo), 1);
}

int	ft_thread(t_philo *philo)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * philo->nb_philo);
	if (!pid)
		return (printf("Error malloc philos\n"), 0);
	if (ft_creating_process(philo, pid) == 0)
		return (free(pid), 0);
	free(pid);
	return (1);
}
