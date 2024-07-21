/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/07/21 06:56:31 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>

void	*ft_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (ft_time(philo, 1) == 0)
		return (NULL);
	philo->timeeating = philo->timestart;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 100);
	while (philo->nb_philo != 1)
	{
		if (ft_thinking(philo) == 0)
			return (NULL);
		if (ft_eating(philo) == 0)
			return (NULL);
		if (philo->nb_eat == 0)
			return (NULL);
		if (ft_sleeping(philo) == 0)
			return (NULL);
		if (ft_get_die_status(philo) == 1)
			return (NULL);
	}
	ft_one_philo(philo);
	return (NULL);
}

void	ft_main_thread(t_philo *philo)
{
	while (philo)
	{
		if (ft_get_die_status(philo) == 1)
		{
			pthread_mutex_lock(philo->mutexprintf);
			ft_all_set_to_dead(philo);
			return ;
		}
		if (ft_check_if_all_finish_eat(philo) == 1)
			return ;
		usleep(10);
		philo = philo->before;
	}
}

int	ft_thinking(t_philo *philo)
{
	if (ft_get_die_status(philo) == 1)
		return (0);
	if (ft_printf("%lld %d is thinking\n", philo->timethinking, philo) == 0)
		return (0);
	philo->timethinking = ft_time(philo, 2);
	if (philo->timethinking == 0)
		return (0);
	return (1);
}

int	ft_eating(t_philo *philo)
{
	if (philo->nb_philo % 2 != 0 || philo->id % 2 == 0)
	{
		if (ft_taking_fork(philo, philo->before->mutexfork) == 0)
			return (0);
		if (ft_taking_fork(philo, philo->mutexfork) == 0)
			return (pthread_mutex_unlock(philo->before->mutexfork), 0);
	}
	else
	{
		if (ft_taking_fork(philo, philo->mutexfork) == 0)
			return (0);
		if (ft_taking_fork(philo, philo->before->mutexfork) == 0)
			return (pthread_mutex_unlock(philo->mutexfork), 0);
	}
	if (ft_get_die_status(philo) == 1)
		return (ft_drop_fork(philo), 0);
	if (ft_printf("%lld %d is eating\n", 0, philo) == 0)
		return (ft_drop_fork(philo), 0);
	philo->timeeating = ft_time(philo, 1);
	if (philo->timeeating == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_usleep(philo, philo->time_eat) == -1)
		return (ft_drop_fork(philo), 0);
	(ft_drop_fork(philo), ft_get_or_set_nb_eat(philo, 1));
	return (1);
}

int	ft_sleeping(t_philo *philo)
{
	if (ft_get_die_status(philo) == 1)
		return (0);
	if (ft_printf("%lld %d is sleeping\n", philo->timesleeping, philo) == 0)
		return (0);
	philo->timesleeping = ft_time(philo, 2);
	if (philo->timesleeping == 0)
		return (0);
	if (ft_usleep(philo, philo->time_sleep) == -1)
		return (0);
	return (1);
}
