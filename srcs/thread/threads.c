/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/04 05:09:40 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


int ft_rotating(t_philo *philo)
{
	if (ft_change_or_check(philo, philo->before, 2) == 1)
		if (ft_eating(philo, philo->before) == 0)
			return (0);
	if (ft_die(philo, 2) == 1)
		return (0);
	return (ft_thinking(philo));	
}

int ft_philosophers(t_philo *philo)
{
	if (ft_rotating(philo) == 0)
		return (0);
	if (ft_die(philo, 2) == 1)
		return(0);
	return (1);
}

void *ft_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (ft_time(philo, 1) == 0)
		return (NULL);
	ft_thinking(philo);
	if (philo->nb_eat == -1)
	{
		while (1)
			if (ft_philosophers(philo) == 0)
				return (NULL);
	}
	else
	{
		while (philo->nb_eat > 0)
			if (ft_philosophers(philo) == 0)
				return (NULL);
	}
	return (NULL);
}

void ft_init_mutex(t_mutex *mutex)
{
	pthread_mutex_t mutexprintf;
	pthread_mutex_t mutexx;
	pthread_mutex_t mutexfork;
	pthread_mutex_t mutexdie;
	pthread_mutex_t mutexfinish;

	pthread_mutex_init(&mutexx, NULL);
	pthread_mutex_init(&mutexprintf, NULL);
	pthread_mutex_init(&mutexfork, NULL);
	pthread_mutex_init(&mutexdie, NULL);
	pthread_mutex_init(&mutexfinish, NULL);
	mutex->mutex = &mutexx;
	mutex->mutexprintf = &mutexprintf;
	mutex->mutexfork = &mutexfork;
	mutex->mutexdie = &mutexdie;
	mutex->mutexfinish = &mutexfinish;
}

void ft_destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex->mutex);
	pthread_mutex_destroy(mutex->mutexprintf);
	pthread_mutex_destroy(mutex->mutexfork);
	pthread_mutex_destroy(mutex->mutexdie);
	pthread_mutex_destroy(mutex->mutexfinish);
}

void ft_mutex_to_philo(t_mutex *mutex, t_philo *philo)
{
	philo->mutex = mutex->mutex;
	philo->mutexprintf = mutex->mutexprintf;
	philo->mutexfork = mutex->mutexfork;
	philo->mutexdie = mutex->mutexdie;
	philo->mutexfinish = mutex->mutexfinish;

}

int ft_creating_threads(t_philo *philo, pthread_t *threads)
{
	int i;
	int nb_philo;
	t_mutex mutex;

	i = -1;
	nb_philo = philo->nb_philo;
	ft_init_mutex(&mutex);
	while (++i <= nb_philo - 1)
	{
		ft_mutex_to_philo(&mutex, philo);
		if (pthread_create(&threads[i], NULL, &ft_routine, philo) != 0)
			return (printf("Error creating threads %d\n", i), 0);
		philo = philo->next;
	}
	i = -1;
	while (++i <= nb_philo - 1)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("Error waiting threads %d\n", i), 0);
	}
	return (ft_destroy_mutex(&mutex), 1);
}

int ft_thread(t_philo *philo)
{
	pthread_t *threads;

	threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!threads)
		return (printf("Error malloc philos\n"), 0);
	if(ft_creating_threads(philo, threads) == 0)
		return (free(threads), 0);
	free(threads);
	return (1);
}
