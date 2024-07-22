/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 22:16:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	ft_routine(t_philo *philo)
{
	pthread_t thread;

	philo->monitor = &thread;
	sem_post(philo->sem_fork);
	if (ft_init_semaphores2(philo) == -1)
		return ;
	pthread_create(philo->monitor, NULL, (void *)ft_monitoring, philo);
	pthread_detach(*philo->monitor);
	if (ft_time(philo, 1) == 0 || ft_set_last_eat(philo) == 0)
		return ;
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
	return (ft_printf("%lld %d is thinking\n", 0, philo));
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
	(ft_drop_fork(philo), ft_get_or_set_nb_eat(philo, 1));
	return (1);
}

int	ft_sleeping(t_philo *philo)
{
	if (ft_printf("%lld %d is sleeping\n", 0, philo) == 0)
		return (0);
	if (ft_usleep(philo, philo->time_sleep) == -1)
		return (0);
	return (1);
}
