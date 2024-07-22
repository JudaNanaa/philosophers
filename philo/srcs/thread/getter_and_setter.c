/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_and_setter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:14:19 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 05:15:03 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

unsigned long long int	ft_get_last_eat(t_philo *philo)
{
	unsigned long long int	result;

	pthread_mutex_lock(philo->mutex_nb_eat);
	result = philo->timeeating;
	pthread_mutex_unlock(philo->mutex_nb_eat);
	return (result);
}

int	ft_get_if_die(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->mutexdie);
	result = philo->die;
	pthread_mutex_unlock(philo->mutexdie);
	return (result);
}

unsigned long long int	ft_set_last_eat(t_philo *philo)
{
	unsigned long long int	result;

	result = ft_time(philo, 2);
	if (result == 0)
		return (0);
	pthread_mutex_lock(philo->mutex_nb_eat);
	philo->timeeating = result;
	pthread_mutex_unlock(philo->mutex_nb_eat);
	return (1);
}
