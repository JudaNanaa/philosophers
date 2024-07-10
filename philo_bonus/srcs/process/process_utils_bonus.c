/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:48:26 by madamou           #+#    #+#             */
/*   Updated: 2024/07/10 05:32:09 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	ft_printf(char *str, unsigned long long int time, t_philo *philo)
{
	sem_wait(philo->sem_printf);
	time = ft_time(philo, 2) / 1000;
	if (time == 0)
		return (sem_post(philo->sem_printf), 0);
	printf(str, time, philo->id);
	sem_post(philo->sem_printf);
	return (1);
}

int	ft_die(t_philo *philo)
{
	philo->die = 1;
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
		if (time - philo->timeeating >= (unsigned long long)philo->time_die)
			return (ft_die(philo), -1);
	}
	return (1);
}
