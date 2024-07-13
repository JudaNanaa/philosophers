/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 05:20:51 by madamou           #+#    #+#             */
/*   Updated: 2024/07/13 05:46:43 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_semaphore_to_philo(t_sema *semaphore, t_philo *philo)
{
	while (philo)
	{
		philo->sem_fork = semaphore->sem_fork;
		philo->sem_printf = semaphore->sem_print;
		philo = philo->next;
	}
	return (0);
}

int	ft_init_semaphores(t_sema *semaphores)
{
	semaphores->sem_fork = sem_open("fork", O_CREAT, 0600, 0);
	if (semaphores->sem_fork == SEM_FAILED)
		return (printf("Error open semaphore fork\n"), -1);
	semaphores->sem_print = sem_open("print", O_CREAT, 0600, 0);
	if (semaphores->sem_print == SEM_FAILED)
	{
		sem_close(semaphores->sem_fork);
		return (printf("Error open semaphore print\n"), -1);
	}
	sem_post(semaphores->sem_print);
	return (0);
}

void	ft_semaphore_close(t_philo *philo)
{
	if (sem_close(philo->sem_fork) == -1)
		printf("Error when close semaphore fork\n");
	if (sem_close(philo->sem_printf) == -1)
		printf("Error when close semaphore printf");
}
