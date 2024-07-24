/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_and_setter_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:32 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 17:18:05 by madamou          ###   ########.fr       */
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

void	ft_set_nb_eat(t_philo *philo)
{
	if (philo->nb_eat != -1)
		--philo->nb_eat;
}

int	ft_check_if_die(t_philo *philo)
{
	unsigned long long int	time;
	unsigned long long int	die;
	unsigned long long int	last_eat;

	time = 0;
	die = 0;
	last_eat = ft_get_last_eat(philo);
	time = ft_time(philo, 2);
	if (time == 0)
		return (-1);
	time = time - last_eat;
	die = philo->time_die;
	if (time >= die)
		return (1);
	return (0);
}
