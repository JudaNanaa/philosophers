/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 17:12:35 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int ft_pthread_create_for_routine(t_philo *philo)
{	
	if (pthread_create(&philo->monitor, NULL, ft_monitoring, philo) == -1)
		return (-1);
	if (pthread_detach(philo->monitor) == -1)
		return (-1);
	return (0);
}

void	ft_routine(t_philo *philo)
{
	if (ft_pthread_create_for_routine(philo) == -1)
		return ;
	if (ft_set_last_eat(philo) == 0)
		return ;
	while (philo->nb_philo != 1)
	{
		if (ft_thinking(philo) == 0)
			return ;
		if (ft_eating(philo) == 0)
			return ;
		if (philo->nb_eat == 0)
			sem_post(philo->sem_finish);
		while (philo->nb_eat == 0)
			usleep(1000000);
		if (ft_sleeping(philo) == 0)
			return ;
	}
	ft_one_philo(philo);
}

int	ft_thinking(t_philo *philo)
{
	return (ft_printf("%lld %d is thinking\n", philo));
}

int	ft_eating(t_philo *philo)
{
	sem_wait(philo->sem_taking_fork);
	if (ft_taking_fork(philo) == 0)
		return (0);
	if (ft_taking_fork(philo) == 0)
		return (sem_post(philo->sem_fork), 0);
	sem_post(philo->sem_taking_fork);
	philo->timeeating = ft_time(philo, 2);
	if (philo->timeeating == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_printf("%lld %d is eating\n", philo) == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_usleep(philo, philo->time_eat) == -1)
		return (ft_drop_fork(philo), 0);
	(ft_drop_fork(philo), ft_set_nb_eat(philo));
	return (1);
}

int	ft_sleeping(t_philo *philo)
{
	if (ft_printf("%lld %d is sleeping\n", philo) == 0)
		return (0);
	if (ft_usleep(philo, philo->time_sleep) == -1)
		return (0);
	return (1);
}
