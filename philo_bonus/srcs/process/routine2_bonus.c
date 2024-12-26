/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:23:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <semaphore.h>

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
