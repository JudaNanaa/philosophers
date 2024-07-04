/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/07/04 22:50:44 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*ft_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(philo->mutexprintf);
	pthread_mutex_unlock(philo->mutexprintf);
	if (ft_time(philo, 1) == 0)
		return (NULL);
	while (philo->nb_eat != 0)
	{
		if (ft_thinking(philo) == 0)
			return (NULL);
		if (ft_eating(philo) == 0)
			return (NULL);
		if (ft_sleeping(philo) == 0)
			return (NULL);
		if (ft_get_die_status(philo) == 1)
			return (NULL);
	}
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
		philo = philo->before;
	}
}

int	ft_thinking(t_philo *philo)
{
	philo->timethinking = ft_time(philo, 2);
	if (philo->timethinking == 0)
		return (0);
	if (philo->timethinking
		- philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo);
		return (0);
	}
	return (ft_printf("%lld %d is thinking\n", philo->timethinking, philo));
}

int	ft_eating(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (ft_taking_fork(philo, philo->before->mutexfork) == 0)
			return (0);
		if (ft_taking_fork(philo, philo->mutexfork) == 0)
			return (0);
	}
	else
	{
		if (ft_taking_fork(philo, philo->mutexfork) == 0)
			return (0);
		if (ft_taking_fork(philo, philo->before->mutexfork) == 0)
			return (0);
	}
	philo->timeeating = ft_time(philo, 1);
	if (philo->timeeating == 0)
		return (0);
	if (ft_printf("%lld %d is eating\n", philo->timeeating, philo) == 0)
		return (0);
	if (usleep(philo->time_eat * 1000) == -1)
		return (0);
	ft_drop_fork(philo);
	--philo->nb_eat;
	return (1);
}

int	ft_sleeping(t_philo *philo)
{
	if (ft_get_die_status(philo) == 1)
		return (0);
	philo->timesleeping = ft_time(philo, 2);
	if (philo->timesleeping == 0)
		return (0);
	if (ft_printf("%lld %d is sleeping\n", philo->timesleeping, philo) == 0)
		return (0);
	if (philo->timesleeping + philo->time_sleep
		- philo->timestart > (unsigned long long)philo->time_die)
	{
		if (usleep((philo->timesleeping - philo->timestart + philo->time_die)
				* 1000) == -1)
			return (0);
		ft_die(philo);
		return (0);
	}
	if (usleep(philo->time_sleep * 1000) == -1)
		return (0);
	return (1);
}
