/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/07/05 18:01:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_taking_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	if (ft_get_die_status(philo) == 1)
		return (0);
	pthread_mutex_lock(mutex);
	if (ft_get_die_status(philo) == 1)
		return (pthread_mutex_unlock(mutex), 0);
	philo->timeeating = ft_time(philo, 2);
	if (philo->timeeating == 0)
		return (pthread_mutex_unlock(mutex), 0);
	if (philo->timeeating
		- philo->timestart > (unsigned long long)philo->time_die)
	{
		ft_die(philo);
		return (pthread_mutex_unlock(mutex), 0);
	}
	return (ft_printf("%lld %d has taken a fork\n", philo->timeeating, philo));
}

void	ft_drop_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->before->mutexfork);
		pthread_mutex_unlock(philo->mutexfork);
	}
	else
	{
		pthread_mutex_unlock(philo->mutexfork);
		pthread_mutex_unlock(philo->before->mutexfork);
	}
}

int	ft_check_if_all_finish_eat(t_philo *philo)
{
	philo = philo->first;
	while (philo)
	{
		if (ft_get_or_set_nb_eat(philo, 2) != 0)
			return (0);
		philo = philo->next;
	}
	return (1);
}

int	ft_get_or_set_nb_eat(t_philo *philo, int cas)
{
	int	nb;

	nb = -1;
	if (cas == 1)
	{
		pthread_mutex_lock(philo->mutex_nb_eat);
		if (philo->nb_eat != -1)
			--philo->nb_eat;
		pthread_mutex_unlock(philo->mutex_nb_eat);
	}
	if (cas == 2)
	{
		pthread_mutex_lock(philo->mutex_nb_eat);
		nb = philo->nb_eat;
		pthread_mutex_unlock(philo->mutex_nb_eat);
	}
	return (nb);
}
