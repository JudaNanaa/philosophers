/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/12/23 21:13:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

t_state	ft_printf(t_philo *philo, char *message)
{
	unsigned long long int	time;

	pthread_mutex_lock(&philo->data->mutex_printf);
	if (check_if_die(philo) == FINISH)
			return (pthread_mutex_unlock(&philo->data->mutex_printf), FINISH);
	time = get_time();
	if (time == 0)
		return (pthread_mutex_unlock(&philo->data->mutex_printf), FINISH);
	time -= philo->data->time_start;
	if (printf("%lld %d %s\n", time / 1000, philo->id, message) == -1)
		return (pthread_mutex_unlock(&philo->data->mutex_printf), FINISH);
	pthread_mutex_unlock(&philo->data->mutex_printf);
	return (CONTINUE);
}

t_state set_simulation_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_die);
	philo->data->state = FINISH;
	pthread_mutex_unlock(&philo->data->mutex_die);
	return (FINISH);
}

t_state get_simulation_state(t_philo *philo)
{
	t_state state;

	pthread_mutex_lock(&philo->data->mutex_die);
	state = philo->data->state;
	pthread_mutex_unlock(&philo->data->mutex_die);
	return (state);
}

t_state check_if_die(t_philo *philo)
{
	long long int	last_eat;
	long long int	time;

	last_eat = philo->last_meal;
	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	time = get_time();
	if (time == 0)
		return (FINISH);
	if (time - last_eat >= philo->data->time_die)
		return (FINISH);
	return (CONTINUE);
}


t_state	ft_usleep(t_philo *philo, long long time_sleep)
{
	long long	time_start;
	long long	time;

	time_start = get_time();
	if (time_start == 0)
		return (FINISH);
	time = time_start;
	while (time - time_start < time_sleep)
	{
		if (usleep(10) == -1)
			return (FINISH);
		if (check_if_die(philo) == FINISH)
			return (FINISH);
	}
	return (CONTINUE);
}
