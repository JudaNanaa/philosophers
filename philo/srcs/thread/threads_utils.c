/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/07/13 16:56:00 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	ft_printf(char *str, unsigned long long int time, t_philo *philo)
{
	pthread_mutex_lock(philo->mutexprintf);
	if (ft_get_die_status(philo) == 0)
	{
		time = ft_time(philo, 2) / 1000;
		if (time == 0)
			return (pthread_mutex_unlock(philo->mutexprintf), 0);
		printf(str, time, philo->id);
	}
	pthread_mutex_unlock(philo->mutexprintf);
	return (1);
}

int	ft_die(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexdie);
	philo->die = 1;
	pthread_mutex_unlock(philo->mutexdie);
	return (0);
}

int	ft_get_die_status(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->mutexdie);
	result = philo->die;
	pthread_mutex_unlock(philo->mutexdie);
	return (result);
}

int	ft_usleep(t_philo *philo, unsigned long long time_sleep)
{
	unsigned long long	time_start;
	unsigned long long	time;

	time_start = ft_time(philo, 2);
	if (time_start == 0)
		return (-1);
	time = time_start;
	while (time - time_start < time_sleep)
	{
		if (usleep(100) == -1)
			return (-1);
		time = ft_time(philo, 2);
		if (time == 0)
			return (-1);
		if (time - philo->timeeating >= (unsigned long long)philo->time_die)
			return (ft_die(philo), -1);
	}
	return (1);
}

void	ft_all_set_to_dead(t_philo *philo)
{
	unsigned long long int	time_death;
	t_philo					*buff;

	time_death = ft_time(philo, 2);
	if (time_death == 0)
		return ;
	buff = philo;
	printf("%lld %d died\n", time_death / 1000, buff->id);
	pthread_mutex_lock(buff->mutexdie);
	philo = philo->first;
	while (philo)
	{
		philo->die = 1;
		philo = philo->next;
	}
	pthread_mutex_unlock(buff->mutexdie);
	pthread_mutex_unlock(buff->mutexprintf);
}