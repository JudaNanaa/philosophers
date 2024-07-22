/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 05:20:51 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 22:20:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_semaphore_to_philo(t_sema *semaphore, t_philo *philo)
{
	unsigned long long int	time;

	sem_post(semaphore->sem_taking_fork);
	time = ft_time(philo, 1);
	if (time == 0)
		return (-1);
	while (philo)
	{
		philo->sem_fork = semaphore->sem_fork;
		philo->sem_printf = semaphore->sem_print;
		philo->sem_taking_fork = semaphore->sem_taking_fork;
		philo->timestamp = time;
		philo = philo->next;
	}
	return (0);
}

int ft_init_semaphores2(t_philo *philo)
{
	char *nb;

	nb = ft_itoa(philo->id);
	if (!nb)
		return (-1);
	sem_unlink((const char *)nb);
	philo->sem_last_eat = sem_open((const char *)nb, O_CREAT, 0600, 1);
	free(nb);
	if (philo->sem_last_eat == SEM_FAILED)
		return (printf("Error open semaphore last_eat\n"), -1);
	return (0);
}

int	ft_init_semaphores(t_sema *semaphores)
{
	sem_unlink("fork");
	semaphores->sem_fork = sem_open("fork", O_CREAT, 0600, 0);
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
	semaphores->sem_taking_fork = sem_open("taking", O_CREAT, 0600, 0);
	if (semaphores->sem_taking_fork == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		sem_close(semaphores->sem_print);
		return (printf("Error open semaphore taking fork\n"), -1);
	}
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
