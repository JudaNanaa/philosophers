/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 05:20:51 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 16:35:39 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_semaphore_to_philo(t_sema *semaphore, t_philo *philo)
{
	while (philo)
	{
		philo->sem_fork = semaphore->sem_fork;
		philo->sem_printf = semaphore->sem_print;
		philo->sem_taking_fork = semaphore->sem_taking_fork;
		philo->sem_last_eat = semaphore->sem_last_eat;
		philo->sem_finish = semaphore->sem_finish;
		philo->sem_die = semaphore->sem_die;
		philo = philo->next;
	}
	return (0);
}

int	ft_init_semaphores2(t_sema *semaphores)
{
	sem_unlink("last_meal");
	semaphores->sem_last_eat = sem_open("last_meal", O_CREAT, 0600, 1);
	if (semaphores->sem_last_eat == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		sem_close(semaphores->sem_print);
		sem_close(semaphores->sem_taking_fork);
		return (printf("Error open semaphore last_eat\n"), -1);
	}
	sem_unlink("finish");
	semaphores->sem_finish = sem_open("finish", O_CREAT, 0600, 0);
	if (semaphores->sem_finish == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		sem_close(semaphores->sem_print);
		sem_close(semaphores->sem_taking_fork);
		sem_close(semaphores->sem_last_eat);
		return (printf("Error open semaphore finish eat\n"), -1);
	}
	sem_unlink("die");
	semaphores->sem_die = sem_open("die", O_CREAT, 0600, 0);
	return (0);
}

int	ft_init_semaphores(t_sema *semaphores, t_philo *philo)
{
	sem_unlink("fork");
	semaphores->sem_fork = sem_open("fork", O_CREAT, 0600, philo->nb_philo);
	if (semaphores->sem_fork == SEM_FAILED)
		return (printf("Error open semaphore fork\n"), -1);
	sem_unlink("print");
	semaphores->sem_print = sem_open("print", O_CREAT, 0600, 1);
	if (semaphores->sem_print == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		return (printf("Error open semaphore print\n"), -1);
	}
	sem_unlink("taking");
	semaphores->sem_taking_fork = sem_open("taking", O_CREAT, 0600, 1);
	if (semaphores->sem_taking_fork == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		sem_close(semaphores->sem_print);
		return (printf("Error open semaphore taking fork\n"), -1);
	}
	return (ft_init_semaphores2(semaphores));
}

void	ft_semaphore_close(t_philo *philo)
{
	if (sem_close(philo->sem_fork) == -1)
		printf("Error when close semaphore fork\n");
	if (sem_close(philo->sem_printf) == -1)
		printf("Error when close semaphore printf\n");
	if (sem_close(philo->sem_taking_fork) == -1)
		printf("Error when close semaphore taking fork\n");
	if (sem_close(philo->sem_last_eat) == -1)
		printf("Error when close semaphore last eat\n");
	if (sem_close(philo->sem_finish) == -1)
		printf("Error when close semaphore finish\n");
	if (sem_close(philo->sem_die) == -1)
		printf("Error when close semaphore die\n");
}
