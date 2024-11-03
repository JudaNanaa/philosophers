/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 22:42:13 by madamou           #+#    #+#             */
/*   Updated: 2024/11/03 15:22:14 by madamou          ###   ########.fr       */
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
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_unlock(&philo->my_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_unlock(philo->next_fork);
	}
}

int	ft_check_if_all_finish_eat(t_philo *philo)
{
	int i;
	int nb_philo;

	i = 0;
	nb_philo = philo[0].nb_philo;
	while (i < nb_philo)
	{
		if (ft_get_or_set_nb_eat(philo, 2) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_get_or_set_nb_eat(t_philo *philo, int cas)
{
	int	nb;

	nb = -1;
	if (cas == 1)
	{
		pthread_mutex_lock(&philo->mutex_nb_eat);
		if (philo->nb_eat != -1)
			--philo->nb_eat;
		pthread_mutex_unlock(&philo->mutex_nb_eat);
	}
	if (cas == 2)
	{
		pthread_mutex_lock(&philo->mutex_nb_eat);
		nb = philo->nb_eat;
		pthread_mutex_unlock(&philo->mutex_nb_eat);
	}
	return (nb);
}

void	ft_one_philo(t_philo *philo)
{
	if (ft_thinking(philo) == 0)
		return ;
	if (ft_taking_fork(philo, &philo->my_fork) == 0)
		return ;
	if (ft_check_if_die(philo) == 1)
	{
		pthread_mutex_unlock(&philo->my_fork);
		return ;
	}
	if (ft_usleep(philo, philo->time_die) == -1)
	{
		pthread_mutex_unlock(&philo->my_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->my_fork);
	usleep(100000);
}
