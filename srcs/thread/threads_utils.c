/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/07/04 05:09:42 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int ft_finish(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexfinish);
	if (ft_die(philo, 2) == 1)
	{
		if (philo->first->finish == 1)
			return (pthread_mutex_unlock(philo->mutexfinish), 1);
		philo->first->finish = 1;
	}
	pthread_mutex_unlock(philo->mutexfinish);
	return (0);
}

int ft_printf(char *str, unsigned long long int time, t_philo *philo)
{
	pthread_mutex_lock(philo->mutexprintf);
	if (ft_finish(philo) == 0)
	{
		time = ft_time(philo, 2);
		if (time == 0)
			return (0);
		printf(str, time, philo->id);
	}
	pthread_mutex_unlock(philo->mutexprintf);
	return (1);
}

int ft_die(t_philo *philo, int cas)
{
	pthread_mutex_lock(philo->mutexdie);
	if (cas == 1)
		philo->first->die = 1;
	else if (cas == 2)
	{
		if (philo->first->die == 1)
			return (pthread_mutex_unlock(philo->mutexdie), 1);
	}
	pthread_mutex_unlock(philo->mutexdie);
	return (0);
}

int ft_taking_fork(t_philo *philo)
{
	philo->timeeating = ft_time(philo, 2);
	if (philo->timeeating == 0)
		return (0);
	if (philo->timeeating - philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo, 1);
		ft_printf("%lld %d died\n", philo->timeeating, philo);
		return (0);
	}
	return (ft_printf("%lld %d has taken a fork\n", philo->timeeating, philo));
}

int ft_change_or_check(t_philo *philo, t_philo *left, int cas)
{
	pthread_mutex_lock(philo->mutexfork);
	if (cas == 0)
	{
		left->fork = 0;
		philo->fork = 0;
	}
	else if (cas == 1)
	{
		left->fork = 1;
		philo->fork = 1;
	}
	else if (cas == 2)
	{
		if (philo->fork == 1 && left->fork == 1)
			return (pthread_mutex_unlock(philo->mutexfork), 1);
		else
			return (pthread_mutex_unlock(philo->mutexfork), 0);
	}
	pthread_mutex_unlock(philo->mutexfork);
	return (-1);
}

int ft_eating(t_philo *philo, t_philo *left)
{
	ft_change_or_check(philo, left, 0);
	if (ft_taking_fork(philo) == 0) 
		return (0);
	if (ft_taking_fork(philo) == 0) 
		return (0);
	philo->timeeating = ft_time(philo, 1);
	if (philo->timeeating == 0)
		return (0);
	if (ft_printf("%lld %d is eating\n", philo->timeeating, philo) == 0)
		return (0);
	if (usleep(philo->time_eat * 1000) == -1)
		return (0);
	ft_change_or_check(philo, left, 1);
	--philo->nb_eat;
	if (ft_die(philo, 2) == 1)
		return (0);
	if (ft_sleeping(philo) == 0)
		return (0);
	philo->thinking = 0;
	return (1);
}

int ft_sleeping(t_philo *philo)
{
	philo->timesleeping = ft_time(philo, 2);
	if (philo->timesleeping == 0)
		return (0);
	if (ft_printf("%lld %d is sleeping\n", philo->timesleeping, philo) == 0)
		return (0);
	if (philo->timesleeping + philo->time_sleep - philo->timestart
		> (unsigned long long)philo->time_die)
	{
		printf("je suis le philo numero %d\n", philo->id);
		if (usleep((philo->timesleeping - philo->timestart + philo->time_die)
			 * 1000) == -1)
			return (0);
		ft_die(philo, 1);
		ft_printf("%lld %d died\n", philo->timesleeping + philo->timesleeping, philo);
		return (0);
	}
	if (usleep(philo->time_sleep * 1000) == -1)
		return (0);
	return (1);
}

int ft_thinking(t_philo *philo)
{
	philo->timethinking = ft_time(philo, 2);
	if (philo->timethinking == 0)
		return (0);
	if (philo->thinking == 1)
		return (1);
	if (philo->timethinking - philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo, 1);
		ft_printf("%lld %d died\n", philo->timethinking, philo);
		return (0);
	}
	if (philo->thinking == 0)
		philo->thinking = 1;
	return (ft_printf("%lld %d is thinking\n", philo->timethinking, philo));
}

