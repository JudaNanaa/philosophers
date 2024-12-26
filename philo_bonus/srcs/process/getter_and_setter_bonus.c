/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_and_setter_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:32 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:36:16 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <semaphore.h>

t_state set_simulation_finish(t_philo *philo)
{
	long long	actual_time;

	actual_time = (get_time() - philo->data->time_start) / 1000;
	sem_wait(philo->data->sema_printf);
	printf("%lld %d %s\n", actual_time, philo->id, DIE);
	sem_post(philo->data->sema_die);
	return (FINISH);
}

t_state	check_if_die(t_philo *philo)
{
	long long int	actual_time;
	long long int	die;
	long long int	last_eat;

	actual_time = get_time();
	if (actual_time == 0)
		return (FINISH);
	last_eat = philo->last_meal;
	die = philo->data->time_die;
	if (actual_time - last_eat >= die)
		return (set_simulation_finish(philo));
	return (CONTINUE);
}
