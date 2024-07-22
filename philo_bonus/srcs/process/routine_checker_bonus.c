/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checker_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:48:44 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 22:17:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_check_if_finish_eat(t_philo *philo)
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

void *ft_monitoring(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (philo == NULL)
		return (NULL);
	while (1)
	{
		if (ft_check_if_die(philo) == 1)
		{
			ft_semaphore_close(philo);
			(sem_close(philo->sem_last_eat), exit(philo->id));
		}
		usleep(100);
	}
	return (NULL);
}
