/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/06/30 17:22:19 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>

void ft_printf(char *str, unsigned long long int time, t_philo *philo)
{

	pthread_mutex_lock(&philo->mutexprintf);
	printf(str, time, philo->id);
	pthread_mutex_unlock(&philo->mutexprintf);
}

int ft_taking_fork(t_philo *philo)
{
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timeeating = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	if (philo->timeeating - philo->timestart > (unsigned long long)philo->time_die)
	{
		philo->die = 1;
		ft_printf("%lld %d died\n", philo->timeeating, philo);
		return (0);
	}
	ft_printf("%lld %d has taken a fork\n", philo->timeeating, philo);
	return (1);
}

int ft_eating(t_philo *philo, t_philo *left)
{
	pthread_mutex_lock(&philo->mutex);
	philo->fork = 0;
	if (ft_taking_fork(philo) == 0)
		return (0);
	left->fork = 0;
	if (ft_taking_fork(philo) == 0)
		return (0);
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timeeating = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	philo->timestart = philo->timeeating;
	ft_printf("%lld %d is eating\n", philo->timeeating, philo);
	if (usleep(philo->time_eat * 1000) == -1 || ft_sleeping(philo, left) == 0)
		return (0);
	philo->thinking = 0;
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}

int ft_sleeping(t_philo *philo, t_philo *left)
{
	philo->fork = 1;
	left->fork = 1;
	--philo->nb_eat;
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timesleeping = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	ft_printf("%lld %d is sleeping\n", philo->timesleeping, philo);
	if (philo->timesleeping + philo->time_sleep - philo->timestart > (unsigned long long)philo->time_die)
	{
		if (usleep((philo->timesleeping - philo->timestart - philo->time_die) * 1000) == -1)
			return (0);
		philo->die = 1;
		ft_printf("%lld %d died\n", philo->timesleeping + philo->timesleeping - philo->timestart - philo->time_die, philo);
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
	philo->timethinking = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	if (philo->timethinking - philo->timestart > (unsigned long long)philo->time_die)
	{
		philo->die = 1;
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

