/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:17:33 by madamou           #+#    #+#             */
/*   Updated: 2024/12/23 21:16:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 100);
	while (philo->data->nb_philo != 1)
	{
		if (thinking(philo) == FINISH)
			return (NULL);
		if (eating(philo) == FINISH)
			return (NULL);
		if (philo->nb_eat == philo->data->nb_must_eat)
			return (NULL);
		if (sleeping(philo) == FINISH)
			return (NULL);
	}
	one_philo(philo);
	return (NULL);
}

t_state thinking(t_philo *philo)
{
	return (ft_printf(philo, THINK));
}

t_state	eating(t_philo *philo)
{
	if (philo->data->nb_philo % 2 != 0 || philo->id % 2 == 0)
	{
		if (taking_fork(philo, philo->right_fork) == FINISH)
			return (FINISH);
		if (taking_fork(philo, &philo->my_fork) == FINISH)
			return (pthread_mutex_unlock(philo->right_fork), FINISH);
	}
	else
	{
		if (taking_fork(philo, &philo->my_fork) == FINISH)
			return (FINISH);
		if (taking_fork(philo, philo->right_fork) == FINISH)
			return (pthread_mutex_unlock(&philo->my_fork), FINISH);
	}
	if (ft_printf(philo, EAT) == FINISH)
		return (drop_fork(philo), FINISH);
	philo->last_meal = get_time();
	if (ft_usleep(philo, philo->data->time_eat) == FINISH)
		return (drop_fork(philo), FINISH);
	drop_fork(philo);
	return (CONTINUE);
}

t_state	sleeping(t_philo *philo)
{
	unsigned long long time;

	if (ft_printf(philo, SLEEP) == FINISH)
		return (FINISH);
	time = get_time();
	if (time == 0)
		return (FINISH);
	if (ft_usleep(philo, philo->data->time_sleep) == FINISH)
		return (FINISH);
	return (CONTINUE);
}
