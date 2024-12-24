/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:04:57 by madamou           #+#    #+#             */
/*   Updated: 2024/12/24 15:22:08 by madamou          ###   ########.fr       */
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
	if (get_simulation_state(philo) == FINISH)
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

t_state	get_simulation_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->data->mutex_die);
	state = philo->data->state;
	pthread_mutex_unlock(&philo->data->mutex_die);
	return (state);
}

t_state	set_simulation_finish(t_philo *philo)
{
	long long	actual_time;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	pthread_mutex_lock(&philo->data->mutex_die);
	philo->data->state = FINISH;
	pthread_mutex_unlock(&philo->data->mutex_die);
	actual_time = (get_time() - philo->data->time_start) / 1000;
	pthread_mutex_lock(&philo->data->mutex_printf);
	printf("%lld %d %s\n", actual_time, philo->id, DIE);
	pthread_mutex_unlock(&philo->data->mutex_printf);
	return (FINISH);
}

t_state	check_if_die(t_philo *philo)
{
	long long int	last_eat;
	long long int	actual_time;
	long long int	time_die;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	actual_time = get_time();
	if (actual_time == 0)
		return (FINISH);
	last_eat = philo->last_meal;
	time_die = philo->data->time_die;
	if (actual_time - last_eat >= time_die)
		return (set_simulation_finish(philo));
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
		if (usleep(100) == -1)
			return (FINISH);
		if (check_if_die(philo) == FINISH)
			return (FINISH);
		time = get_time();
		if (time == 0)
			return (FINISH);
	}
	return (CONTINUE);
}
