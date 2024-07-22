/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 09:13:04 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	ft_routine(t_philo *philo)
{
	sem_post(philo->sem_fork);
	if (ft_time(philo, 1) == 0)
		return ;
	philo->timeeating = philo->timestart;
	while (philo->nb_philo != 1)
	{
		if (ft_thinking(philo) == 0)
			return ;
		if (ft_eating(philo) == 0)
			return ;
		if (philo->nb_eat == 0)
			return ;
		if (ft_sleeping(philo) == 0)
			return ;
	}
	ft_one_philo(philo);
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
	sem_wait(philo->sem_taking_fork);
	if (ft_taking_fork(philo) == 0)
		return (0);
	if (ft_taking_fork(philo) == 0)
		return (sem_post(philo->sem_fork), 0);
	sem_post(philo->sem_taking_fork);
	philo->timeeating = ft_time(philo, 1);
	if (philo->timeeating == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_printf("%lld %d is eating\n", philo->timeeating, philo) == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_usleep(philo, philo->time_eat) == -1)
		return (ft_drop_fork(philo), 0);
	(ft_drop_fork(philo), --philo->nb_eat);
	return (1);
}

int	ft_sleeping(t_philo *philo)
{
	philo->timesleeping = ft_time(philo, 2);
	if (philo->timesleeping == 0)
		return (0);
	if (ft_printf("%lld %d is sleeping\n", philo->timesleeping, philo) == 0)
		return (0);
	if (ft_usleep(philo, philo->time_sleep) == -1)
		return (0);
	return (1);
}
