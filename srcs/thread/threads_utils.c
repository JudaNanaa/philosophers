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

int ft_eating(t_philo *philo, t_philo *left)
{
	pthread_mutex_lock(&philo->mutex);
	philo->fork = 0;
	left->fork = 0;
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timeeating = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	printf("%lld %d has taken a fork\n", philo->timeeating, philo->id);
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timeeating = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	printf("%lld %d is eating\n", philo->timeeating, philo->id);
	usleep(philo->time_eat * 1000);
	ft_sleeping(philo, left);
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
	printf("%lld %d is sleeping\n", philo->timesleeping, philo->id);
	if (usleep(philo->time_sleep * 1000) == -1)
		return (0);
	return (1);
}

int ft_thinking(t_philo *philo)
{
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (0);
	philo->timethinking = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	printf("%lld %d is thinking\n", philo->timethinking, philo->id);
	philo->thinking = 1;
	return (1);
}

