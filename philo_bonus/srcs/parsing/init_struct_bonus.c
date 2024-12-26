/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:12:50 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:27:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

int set_data(t_data *data)
{
	data->time_die *= 1000;
	data->time_eat *= 1000;
	data->time_sleep *= 1000;
	if (data->nb_philo % 2 == 0)
		data->time_think = data->time_eat - data->time_sleep;
	else
		data->time_think = (data->time_eat * 2) - data->time_sleep;
	(sem_unlink("fork"), sem_unlink("die"), sem_unlink("print"));
	data->sema_fork = sem_open("fork", O_CREAT, 0600, data->nb_philo);
	if (data->sema_fork == SEM_FAILED)
		return (printf("Error open semaphore fork\n"), EXIT_FAILURE);
	data->sema_printf = sem_open("print", O_CREAT, 0600, 1);
	if (data->sema_printf == SEM_FAILED)
	{
		sem_close(data->sema_fork);
		return (printf("Error open semaphore print\n"), EXIT_FAILURE);
	}
	data->sema_die = sem_open("die", O_CREAT, 0600, 0);
	if (data->sema_die == SEM_FAILED)
	{
		(sem_close(data->sema_fork), sem_close(data->sema_fork));
		return (printf("Error open semaphore print\n"), EXIT_FAILURE);
	}
	sem_unlink("taking_fork");
	data->sema_taking_fork = sem_open("taking_fork", O_CREAT, 0600, 1);
	if (data->sema_taking_fork == SEM_FAILED)
	{
		sem_close(data->sema_die);
		(sem_close(data->sema_fork), sem_close(data->sema_fork));
		return (printf("Error open semaphore print\n"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	if (set_data(data) == EXIT_FAILURE)
		return (NULL);
	philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, sizeof(t_philo) * data->nb_philo);
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		i++;
	}
	return (philos);
}
