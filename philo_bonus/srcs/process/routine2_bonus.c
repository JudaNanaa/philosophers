/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/07/10 05:32:23 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_taking_fork(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	philo->timeeating = ft_time(philo, 2);
	if (philo->timeeating == 0)
		return (sem_post(philo->sem_fork), 0);
	if (philo->timeeating
		- philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo);
		return (sem_post(philo->sem_fork), 0);
	}
	return (ft_printf("%lld %d has taken a fork\n", philo->timeeating, philo));
}

void	ft_drop_fork(t_philo *philo)
{
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
}

void	ft_one_philo(t_philo *philo)
{
	if (ft_thinking(philo) == 0)
		return ;
	if (ft_taking_fork(philo) == 0)
		return ;
	if (ft_usleep(philo, philo->time_die) == -1)
	{
		sem_post(philo->sem_fork);
		return ;
	}
	ft_die(philo);
}
