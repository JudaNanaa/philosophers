/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:12:50 by madamou           #+#    #+#             */
/*   Updated: 2024/12/23 21:08:41 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

void	set_data(t_data *data)
{
	data->time_die *= 1000;
	data->time_eat *= 1000;
	data->time_sleep *= 1000;
	data->state = CONTINUE;
	pthread_mutex_init(&data->mutex_die, NULL); // TODO: protect this
	pthread_mutex_init(&data->mutex_printf, NULL); // TODO: protect this
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	set_data(data);
	philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, sizeof(t_philo) * data->nb_philo);
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].my_fork, NULL); // TODO: protect this
		philos[i].right_fork = &philos[(i + 1) % data->nb_philo].my_fork;
		i++;
	}
	return (philos);
}
