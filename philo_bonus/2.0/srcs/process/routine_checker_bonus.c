/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checker_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:05:15 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 15:41:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	*ft_monitoring(void *args)
{
	t_philo			*philo;
	long long int	time;

	philo = (t_philo *)args;
	if (philo == NULL)
		return (NULL);
	while (1)
	{
		if (ft_check_if_die(philo) == 1)
		{
			time = ft_time(philo, 2);
			sem_wait(philo->sem_printf);
			if (time == 0)
				return (sem_post(philo->sem_printf), NULL);
			printf("%lld %d died\n", (time - philo->timestamp) / 1000,
				philo->id);
			sem_post(philo->sem_die);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}
