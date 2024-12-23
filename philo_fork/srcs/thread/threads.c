/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/12/23 21:15:01 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

void	ft_destroy_mutex(t_mutex *mutex, t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		nb_philos;

	i = 0;
	nb_philos = philo[0].data->nb_philo;
	tmp = philo;
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&philo[i].my_fork);
		i++;
	}
	pthread_mutex_destroy(&mutex->mutexprintf);
	pthread_mutex_destroy(&mutex->mutexdie);
}

int	ft_thread(t_philo *philos)
{
	int		i;
	int		nb_philo;
	long long time_start;
	t_mutex	mutex;

	i = 0;
	nb_philo = philos[0].data->nb_philo;
	time_start = get_time();
	philos->data->time_start = time_start;
	while (i < nb_philo)
	{
		philos[i].last_meal = time_start;	
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (printf("Error creating threads %d\n", i), 0);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (printf("Error waiting threads %d\n", i), 0);
		i++;
	}
	return (ft_destroy_mutex(&mutex, philos), 1);
}
