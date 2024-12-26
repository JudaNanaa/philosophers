/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:36:34 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <bits/pthreadtypes.h>
#include <semaphore.h>
#include <stdio.h>

void *monitor(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	sem_wait(philo->data->sema_die);
	sem_post(philo->data->sema_die);
	free(&philo[0 - philo->id]);
	exit(EXIT_SUCCESS);
}

int	pthread_create_for_routine(t_philo *philo)
{
	pthread_t thread;
	
	if (pthread_create(&thread, NULL, monitor, philo) == -1)
		return (-1);
	if (pthread_detach(thread) == -1)
		return (-1);
	return (0);
}

void	routine(t_philo *philo)
{
	if (pthread_create_for_routine(philo) == -1)
		return ;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 100);
	if (philo->data->nb_philo == 0)
		return;
	while (philo->data->nb_philo != 1)
	{
		if (eating(philo) == FINISH)
			return ;
		if (philo->nb_eat == philo->data->nb_must_eat)
		{
			free(&philo[0 - philo->id -1]);
			exit(EXIT_SUCCESS);
		}
		if (sleeping(philo) == FINISH)
			return ;
		if (thinking(philo) == FINISH)
			return ;
	}
	one_philo(philo);
}

t_state	thinking(t_philo *philo)
{
	if (ft_printf(philo, THINK) == FINISH)
		return (FINISH);
	return (ft_usleep(philo, philo->data->time_think));
}

t_state	eating(t_philo *philo)
{
	sem_wait(philo->data->sema_taking_fork);
	if (taking_fork(philo) == FINISH)
		return (FINISH);
	if (taking_fork(philo) == FINISH)
		return (sem_post(philo->data->sema_fork), FINISH);
	sem_post(philo->data->sema_taking_fork);
	philo->last_meal = get_time();
	if (philo->last_meal == 0)
		return (drop_fork(philo), FINISH);
	if (ft_printf(philo, EAT) == FINISH)
		return (drop_fork(philo), FINISH);
	if (ft_usleep(philo, philo->data->time_eat) == FINISH)
		return (drop_fork(philo), FINISH);
	drop_fork(philo);
	return (CONTINUE);
}

t_state sleeping(t_philo *philo)
{
	if (ft_printf(philo, SLEEP) == FINISH)
		return (FINISH);
	return (ft_usleep(philo, philo->data->time_sleep));
}
