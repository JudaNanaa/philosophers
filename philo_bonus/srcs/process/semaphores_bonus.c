/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 05:20:51 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 09:53:44 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_semaphore_to_philo(t_sema *semaphore, t_philo *philo)
{
	sem_post(semaphore->sem_taking_fork);
	while (philo)
	{
		philo->sem_fork = semaphore->sem_fork;
		philo->sem_printf = semaphore->sem_print;
		philo->sem_taking_fork = semaphore->sem_taking_fork;
		philo = philo->next;
	}
	return (0);
}

int	ft_init_semaphores(t_sema *semaphores)
{
	sem_unlink("fork");
	semaphores->sem_fork = sem_open("fork", O_CREAT, 0600, 0);
	if (semaphores->sem_fork == SEM_FAILED)
		return (printf("Error open semaphore fork\n"), -1);
	sem_unlink("print");
	semaphores->sem_print = sem_open("print", O_CREAT, 0600, 0);
	if (semaphores->sem_print == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		return (printf("Error open semaphore print\n"), -1);
	}
	sem_unlink("taking");
	semaphores->sem_taking_fork = sem_open("taking", O_CREAT, 0600, 0);
	if (semaphores->sem_taking_fork == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		sem_close(semaphores->sem_print);
		return (printf("Error open semaphore taking fork\n"), -1);
	}
	sem_post(semaphores->sem_print);
	return (0);
}

void	ft_semaphore_close(t_philo *philo)
{
	if (sem_close(philo->sem_fork) == -1)
		printf("Error when close semaphore fork\n");
	if (sem_close(philo->sem_printf) == -1)
		printf("Error when close semaphore printf\n");
	if (sem_close(philo->sem_taking_fork) == -1)
		printf("Error when close semaphore taking fork\n");
}
