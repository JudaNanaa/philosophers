/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/12/24 15:31:56 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

void	ft_destroy_mutex(t_philo *philos, t_data *data)
{
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = data->nb_philo;
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&philos[i].my_fork);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_printf);
	pthread_mutex_destroy(&data->mutex_die);
}

int	ft_thread(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	data->time_start = get_time();
	while (i < data->nb_philo)
	{
		philos[i].last_meal = data->time_start;
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (printf("Error creating threads %d\n", i), 0);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (printf("Error waiting threads %d\n", i), 0);
		i++;
	}
	return (ft_destroy_mutex(philos, data), 1);
}
