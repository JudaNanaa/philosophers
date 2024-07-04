/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/07/04 22:42:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int ft_taking_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	if (ft_get_die_status(philo) == 1)
		return (0);
	pthread_mutex_lock(mutex);
	philo->timeeating = ft_time(philo, 2);
	if (philo->timeeating == 0)
		return (0);
	if (philo->timeeating - philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo);
		return (0);
	}
	return (ft_printf("%lld %d has taken a fork\n", philo->timeeating, philo));
}

void ft_drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->before->mutexfork);
		pthread_mutex_unlock(philo->mutexfork);
	}
	else
	{
		pthread_mutex_unlock(philo->mutexfork);
		pthread_mutex_unlock(philo->before->mutexfork);
	}
}