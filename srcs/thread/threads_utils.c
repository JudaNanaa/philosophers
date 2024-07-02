/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/07/02 12:32:46 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int ft_finish(t_philo *philo, t_philo *buff)
{
	pthread_mutex_lock(philo->mutexfinish);
	if (ft_die(philo, NULL, 2) == 1)
	{
		buff = philo->first;
		while (buff)
		{
			if (buff->finish == 1)
				return (pthread_mutex_unlock(philo->mutexfinish), 1);
			buff = buff->next;
		}
		philo->first->finish = 1;
		usleep(10000);
	}
	pthread_mutex_unlock(philo->mutexfinish);
	return (0);
}

void ft_printf(char *str, unsigned long long int time, t_philo *philo)
{
	if (philo->id == 2)
		printf("je suis dans le thread 2\n");
	pthread_mutex_lock(philo->mutexprintf);
	if (ft_finish(philo, NULL) == 0)
	{
		gettimeofday(&philo->curent_time, NULL);
		time = (philo->curent_time.tv_sec * 1000)
			+ (philo->curent_time.tv_usec / 1000);
		printf(str, time, philo->id);
	}
	pthread_mutex_unlock(philo->mutexprintf);
}

int ft_die(t_philo *philo, t_philo *buff, int cas)
{
	pthread_mutex_lock(philo->mutexdie);
	if (cas == 1)
	{
		philo->die = 1;
	}
	else if (cas == 2)
	{
		buff = philo->first;
		while (buff)
		{
			if (buff->die == 1)
				return (pthread_mutex_unlock(philo->mutexdie), 1);
			buff = buff->next;
		}
	}
	pthread_mutex_unlock(philo->mutexdie);
	return (0);
}

int ft_taking_fork(t_philo *philo)
{
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timeeating = ((philo->curent_time.tv_sec * 1000000)
		+ philo->curent_time.tv_usec) / 1000;
	if (philo->timeeating - philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo, NULL, 1);
		ft_printf("%lld %d died\n", philo->timeeating, philo);
		return (0);
	}
	ft_printf("%lld %d has taken a fork\n", philo->timeeating, philo);
	return (1);
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
	ft_change_or_check(philo, left,0);
	if (ft_taking_fork(philo) == 0)
		return (pthread_mutex_unlock(philo->mutex), 0);
	if (ft_taking_fork(philo) == 0)
		return (pthread_mutex_unlock(philo->mutex), 0);
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (pthread_mutex_unlock(philo->mutex), 0);
	philo->timeeating = ((philo->curent_time.tv_sec * 1000000)
		+ philo->curent_time.tv_usec) / 1000;
	philo->timestart = philo->timeeating;
	ft_printf("%lld %d is eating\n", philo->timeeating, philo);
	if (usleep(philo->time_eat * 1000) == -1)
		return (pthread_mutex_unlock(philo->mutex), 0);
	ft_change_or_check(philo, left, 1);
	--philo->nb_eat;
	if (ft_die(philo, NULL, 2) == 1)
		return (pthread_mutex_unlock(philo->mutex), 0);
	if (ft_sleeping(philo) == 0)
		return (pthread_mutex_unlock(philo->mutex), 0);
	philo->thinking = 0;
	return (1);
}

int ft_sleeping(t_philo *philo)
{
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timesleeping = (philo->curent_time.tv_sec * 1000)
		+ (philo->curent_time.tv_usec / 1000);
	ft_printf("%lld %d is sleeping\n", philo->timesleeping, philo);
	if (philo->timesleeping + philo->time_sleep - philo->timestart
		>= (unsigned long long)philo->time_die)
	{
		if (usleep((philo->timesleeping - philo->timestart + philo->time_die)
			 * 1000) == -1)
			return (0);
		ft_die(philo, NULL, 1);
		ft_printf("%lld %d died\n", philo->timesleeping + philo->timesleeping, philo);
		return (0);
	}
	if (usleep(philo->time_sleep * 1000) == -1)
		return (0);
	return (1);
}

int ft_thinking(t_philo *philo)
{
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timethinking = ((philo->curent_time.tv_sec * 1000000)
		+ philo->curent_time.tv_usec) / 1000;
	if (philo->timethinking - philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo, NULL, 1);
		ft_printf("%lld %d died\n", philo->timethinking, philo);
		return (0);
	}
	if (philo->thinking == 0)
	{
		ft_printf("%lld %d is thinking\n", philo->timethinking, philo);
		philo->thinking = 1;
	}	
	return (1);
}

