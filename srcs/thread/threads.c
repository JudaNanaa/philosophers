/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/06/30 23:03:37 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


int ft_mutex(t_philo *philo)
{
	if (philo->id != 1 && philo->id != philo->nb_philo)
		if (philo->fork == 1 && philo->before->fork == 1)
			if (ft_eating(philo, philo->before) == 0)
				return (0);
	if (philo->id == 1)
		if (philo->fork == 1 && philo->last->fork == 1)
			if (ft_eating(philo, philo->last) == 0)
				return (0);
	if (philo->id == philo->nb_philo)
		if (philo->fork == 1 && philo->first->fork == 1)
			if (ft_eating(philo, philo->first) == 0)
				return (0);
	return (ft_thinking(philo));	
}

void *ft_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (gettimeofday(&philo->curent_time, NULL) == -1)
		return (NULL);
	philo->timestart = ((philo->curent_time.tv_sec * 1000000) + philo->curent_time.tv_usec) / 1000;
	if (philo->nb_eat == -1)
	{
		while (1)
		{
			if (ft_mutex(philo) == 0)
				return (NULL);
			if (ft_check_if_die(philo)== 0)
				return (NULL);
		}
	}
	else {
		while (philo->nb_eat > 0)
		{
			if (ft_mutex(philo) == 0)
				return (NULL);
			if (ft_check_if_die(philo) == 0)
				return (NULL);
		}
	}
	return (NULL);
}

int ft_creating_threads(t_philo *philo, pthread_t *threads)
{
	int i;
	int nb_philo;
	pthread_mutex_t mutex;
	pthread_mutex_t mutexprintf;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutexprintf, NULL);
	i = 0;
	nb_philo = philo->nb_philo;
	while (i <= nb_philo - 1)
	{
		philo->mutex = mutex;
		philo->mutexprintf = mutexprintf;
		if (pthread_create(&threads[i], NULL, &ft_routine, philo) != 0)
			return (printf("Error creating threads %d\n", i), 0);
		philo = philo->next;
		++i;
	}
	i = 0;
	while (i <= nb_philo - 1)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("Error waiting threads %d\n", i), 0);
		++i;
	}
	pthread_mutex_destroy(&mutex);
	return (1);
}

int ft_thread(t_philo *philo)
{
	pthread_t *threads;
	int i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!threads)
		return (printf("Error malloc philos\n"), 0);
	if(ft_creating_threads(philo, threads) == 0)
		return (free(threads), 0);
	free(threads);
	return (1);
}
