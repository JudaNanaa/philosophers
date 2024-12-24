/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/12/24 02:22:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>

int	taking_one_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (FINISH);
	return (ft_printf(philo, FORK));
}

void	drop_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->my_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	one_philo(t_philo *philo)
{
	if (taking_one_fork(philo, &philo->my_fork) == FINISH)
		return ;
	if (check_if_die(philo) == FINISH)
	{
		pthread_mutex_unlock(&philo->my_fork);
		return ;
	}
	if (ft_usleep(philo, philo->data->time_die) == FINISH)
	{
		pthread_mutex_unlock(&philo->my_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->my_fork);
	printf("%ld %d %s", philo->data->time_die, philo->id, DIE);
}
