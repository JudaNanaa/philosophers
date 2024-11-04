/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/11/04 13:55:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	ft_printf(char *str, t_philo *philo)
{
	unsigned long long int	time;

	pthread_mutex_lock(philo->mutexprintf);
	if (ft_get_if_die(philo) == 0)
	{
		time = ft_time(philo, 2);
		if (time == 0)
			return (pthread_mutex_unlock(philo->mutexprintf), 0);
		printf(str, (time - philo->timestart) / 1000, philo->id);
	}
	pthread_mutex_unlock(philo->mutexprintf);
	return (1);
}

int	ft_check_if_die(t_philo *philo)
{
	unsigned long long int	last_eat;
	unsigned long long int	time;

	last_eat = ft_get_last_eat(philo);
	time = ft_time(philo, 2);
	if (time == 0)
		return (-1);
	if (time - last_eat >= (unsigned long long int)philo->time_die)
		return (1);
	return (0);
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
		if (usleep(10) == -1)
			return (-1);
		time = ft_time(philo, 2);
		if (time == 0)
			return (-1);
		if (ft_get_if_die(philo) == 1)
			return (-1);
	}
	return (1);
}

void	ft_all_set_to_dead(t_philo *philo)
{
	unsigned long long int	time_death;
	t_philo					*buff;
	int						i;

	time_death = ft_time(philo, 2);
	if (time_death == 0)
		return ;
	buff = philo;
	printf("%lld %d died\n", (time_death - philo->timestart) / 1000, buff->id);
	pthread_mutex_lock(buff->mutexdie);
	i = 0;
	while (i < philo[0].nb_philo)
	{
		philo[i].die = 1;
		i++;
	}
	pthread_mutex_unlock(buff->mutexdie);
	pthread_mutex_unlock(buff->mutexprintf);
}
