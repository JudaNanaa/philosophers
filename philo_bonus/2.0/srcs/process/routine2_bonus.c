/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 14:18:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_taking_fork(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	return (ft_printf("%lld %d has taken a fork\n", philo));
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
	usleep(1000000);
}
