/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:48:26 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:23:44 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <semaphore.h>

t_state	ft_printf(t_philo *philo, char *message)
{
	unsigned long long int	time;

	sem_wait(philo->data->sema_printf);
	if (check_if_die(philo) == FINISH)
		return (sem_post(philo->data->sema_printf), FINISH);
	time = get_time();
	if (time == 0)
		return (sem_post(philo->data->sema_printf), FINISH);
	time -= philo->data->time_start;
	if (printf("%lld %d %s\n", time / 1000, philo->id, message) == -1)
		return (sem_post(philo->data->sema_printf), FINISH);
	sem_post(philo->data->sema_printf);
	return (CONTINUE);
}

t_state	ft_usleep(t_philo *philo, long long time_sleep)
{
	long long	time_start;
	long long	actual_time;

	time_start = get_time();
	if (time_start == 0)
		return (FINISH);
	actual_time = time_start;
	while (actual_time - time_start < time_sleep)
	{
		if (usleep(100) == -1)
			return (FINISH);
		if (check_if_die(philo) == FINISH)
			return (FINISH);
		actual_time = get_time();
		if (actual_time == 0)
			return (FINISH);
	}
	return (CONTINUE);
}
