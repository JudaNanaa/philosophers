/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2025/01/17 22:58:29 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <semaphore.h>

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	sem_wait(philo->data->sema_die);
	sem_post(philo->data->sema_die);
	free(&philo[0 - philo->id]);
	exit(EXIT_SUCCESS);
}

t_state	taking_fork(t_philo *philo)
{
	sem_wait(philo->data->sema_fork);
	if (ft_printf(philo, FORK) == FINISH)
		return (sem_post(philo->data->sema_fork), FINISH);
	return (CONTINUE);
}

void	drop_fork(t_philo *philo)
{
	sem_post(philo->data->sema_fork);
	sem_post(philo->data->sema_fork);
}

void	one_philo(t_philo *philo)
{
	if (taking_fork(philo) == FINISH)
		return ;
	if (ft_usleep(philo, philo->data->time_die) == FINISH)
	{
		sem_post(philo->data->sema_fork);
		return ;
	}
	printf("%ld %d %s", philo->data->time_die, philo->id, DIE);
}
