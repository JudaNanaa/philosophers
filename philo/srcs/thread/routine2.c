/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/07/25 19:05:48 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_taking_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	return (ft_printf("%lld %d has taken a fork\n", philo));
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

void	ft_one_philo(t_philo *philo)
{
	if (ft_thinking(philo) == 0)
		return ;
	if (ft_taking_fork(philo, philo->mutexfork) == 0)
		return ;
	if (ft_check_if_die(philo) == 1)
	{
		pthread_mutex_unlock(philo->mutexfork);
		return ;
	}
	if (ft_usleep(philo, philo->time_die) == -1)
	{
		pthread_mutex_unlock(philo->mutexfork);
		return ;
	}
	pthread_mutex_unlock(philo->mutexfork);
	usleep(100000);
}
