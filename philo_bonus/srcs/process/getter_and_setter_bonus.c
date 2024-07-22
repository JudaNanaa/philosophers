/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_and_setter_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:32 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 22:23:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

unsigned long long int	ft_get_last_eat(t_philo *philo)
{
	unsigned long long int	result;

	sem_wait(philo->sem_last_eat);
	result = philo->timeeating;
	sem_post(philo->sem_last_eat);
	return (result);
}

int	ft_get_if_die(t_philo *philo)
{
	int	result;

	sem_wait(philo->sem_last_eat);
	result = philo->die;
	sem_post(philo->sem_last_eat);
	return (result);
}

unsigned long long int	ft_set_last_eat(t_philo *philo)
{
	unsigned long long int	result;

	result = ft_time(philo, 2);
	if (result == 0)
		return (0);
	sem_wait(philo->sem_last_eat);
	philo->timeeating = result;
	sem_post(philo->sem_last_eat);
	return (1);
}

int	ft_get_or_set_nb_eat(t_philo *philo, int cas)
{
	int	nb;

	nb = -1;
	if (cas == 1)
	{
		sem_wait(philo->sem_last_eat);
		if (philo->nb_eat != -1)
			--philo->nb_eat;
		sem_post(philo->sem_last_eat);
	}
	if (cas == 2)
	{
		sem_wait(philo->sem_last_eat);
		nb = philo->nb_eat;
		sem_post(philo->sem_last_eat);
	}
	return (nb);
}

int	ft_check_if_die(t_philo *philo)
{
	unsigned long long int	time;
	unsigned long long int	die;
	
	time = ft_time(philo, 2);
	if (time == 0)
		return (-1);
	time = time - ft_get_last_eat(philo);
	die = philo->time_die;
	if (time >= die)
		return (1);
	return (0);
}