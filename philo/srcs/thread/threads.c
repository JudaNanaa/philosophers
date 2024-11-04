/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/11/04 13:54:44 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int	ft_init_mutex(t_mutex *mutex)
{
	pthread_mutex_init(&mutex->mutexprintf, NULL);
	pthread_mutex_init(&mutex->mutexdie, NULL);
	return (1);
}

void	ft_destroy_mutex(t_mutex *mutex, t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		nb_philos;

	i = 0;
	nb_philos = philo[0].nb_philo;
	tmp = philo;
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&philo[i].my_fork);
		i++;
	}
	pthread_mutex_destroy(&mutex->mutexprintf);
	pthread_mutex_destroy(&mutex->mutexdie);
}

int	ft_mutex_to_philo(t_mutex *mutex, t_philo *philo)
{
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = philo[0].nb_philo;
	if (ft_time(philo, 1) == 0)
		return (0);
	while (i < nb_philos)
	{
		pthread_mutex_init(&philo[i].my_fork, NULL);
		pthread_mutex_init(&philo[i].mutex_nb_eat, NULL);
		if (i == 0)
			philo[i].next_fork = &philo[nb_philos - 1].my_fork;
		else
			philo[i].next_fork = &philo[i - 1].my_fork;
		philo[i].mutexprintf = &mutex->mutexprintf;
		philo[i].mutexdie = &mutex->mutexdie;
		philo[i].timestart = philo[0].timestart;
		philo[i].timeeating = philo[0].timestart;
		i++;
	}
	return (1);
}

int	ft_creating_threads(t_philo *philo, pthread_t *threads)
{
	int		i;
	int		nb_philo;
	t_mutex	mutex;

	i = 0;
	nb_philo = philo[0].nb_philo;
	if (ft_init_mutex(&mutex) == 0 || ft_mutex_to_philo(&mutex, philo) == 0)
		return (0);
	while (i < nb_philo)
	{
		if (pthread_create(&threads[i], NULL, &ft_routine, &philo[i]) != 0)
			return (printf("Error creating threads %d\n", i), 0);
		i++;
	}
	ft_main_thread(philo);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("Error waiting threads %d\n", i), 0);
		i++;
	}
	return (ft_destroy_mutex(&mutex, philo), 1);
}

int	ft_thread(t_philo *philo)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * philo[0].nb_philo);
	if (!threads)
		return (printf("Error malloc philos\n"), 0);
	if (ft_creating_threads(philo, threads) == 0)
		return (free(threads), 0);
	free(threads);
	return (1);
}
