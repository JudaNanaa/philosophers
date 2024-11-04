/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/11/04 13:53:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*ft_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 100);
	while (philo->nb_philo != 1)
	{
		if (ft_thinking(philo) == 0)
			return (NULL);
		if (philo->nb_eat == 0 || ft_eating(philo) == 0)
			return (NULL);
		if (philo->nb_eat == 0)
			return (NULL);
		if (ft_sleeping(philo) == 0)
			return (NULL);
	}
	ft_one_philo(philo);
	return (NULL);
}

void	ft_main_thread(t_philo *philo)
{
	int	i;
	int	nb_philo;

	i = 0;
	nb_philo = philo[0].nb_philo;
	while (1)
	{
		if (ft_check_if_die(philo) == 1)
		{
			pthread_mutex_lock(philo->mutexprintf);
			ft_all_set_to_dead(philo);
			return ;
		}
		if (ft_check_if_all_finish_eat(philo) == 1)
			return ;
		usleep(10);
		i++;
		if (i == nb_philo)
			i = 0;
	}
}

int	ft_thinking(t_philo *philo)
{
	return (ft_printf("%lld %d is thinking\n", philo));
}

int	ft_eating(t_philo *philo)
{
	if (philo->nb_philo % 2 != 0 || philo->id % 2 == 0)
	{
		if (ft_taking_fork(philo, philo->next_fork) == 0)
			return (0);
		if (ft_taking_fork(philo, &philo->my_fork) == 0)
			return (pthread_mutex_unlock(philo->next_fork), 0);
	}
	else
	{
		if (ft_taking_fork(philo, &philo->my_fork) == 0)
			return (0);
		if (ft_taking_fork(philo, philo->next_fork) == 0)
			return (pthread_mutex_unlock(&philo->my_fork), 0);
	}
	if (ft_printf("%lld %d is eating\n", philo) == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_set_last_eat(philo) == 0)
		return (ft_drop_fork(philo), 0);
	if (ft_usleep(philo, philo->time_eat) == -1)
		return (ft_drop_fork(philo), 0);
	(ft_drop_fork(philo), ft_get_or_set_nb_eat(philo, 1));
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
