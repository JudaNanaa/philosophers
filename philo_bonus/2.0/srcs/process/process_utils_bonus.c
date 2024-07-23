/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:48:26 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 16:06:34 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_printf(char *str, t_philo *philo)
{
	unsigned long long int time;

	time = ft_time(philo, 2) / 1000;
	if (time == 0)
		return (0);
	sem_wait(philo->sem_printf);
	printf(str, time - philo->timestamp / 1000, philo->id);
	sem_post(philo->sem_printf);
	return (1);
}

int	ft_usleep(t_philo *philo, unsigned long long time_sleep)
{
	unsigned long long	time_start;
	unsigned long long	time;

	time_start = ft_time(philo, 2);
	if (time_start == 0)
		return (-1);
	time = time_start;
	while (time - time_start < time_sleep)
	{
		if (usleep(10) == -1)
			return (-1);
		time = ft_time(philo, 2);
		if (time == 0)
			return (-1);
	}
	return (1);
}
