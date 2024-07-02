/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/02 12:39:51 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


int ft_mutex(t_philo *philo)
{
	if (philo->id != 1)
		if (ft_change_or_check(philo, philo->before, 2) == 1)
			if (ft_eating(philo, philo->before) == 0)
				return (0);
	if (philo->id == 1)
		if (ft_change_or_check(philo, philo->last, 2) == 1)
			if (ft_eating(philo, philo->last) == 0)
				return (0);
	if (ft_die(philo, NULL, 2) == 1)
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
	ft_thinking(philo);
	if (philo->nb_eat == -1)
	{
		while (1)
		{
			if (ft_mutex(philo) == 0)
				return (NULL);
			if (ft_die(philo, NULL, 2) == 1)
				return (NULL);
		}
	}
	else {
		while (philo->nb_eat > 0)
		{
			if (ft_mutex(philo) == 0)
				return (NULL);
			if (ft_die(philo, NULL, 2) == 1)
				return (NULL);
		}
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

int ft_creating_threads(t_philo *philo, pthread_t *threads)
{
	int i;
	int nb_philo;
	t_mutex mutex;

	i = 0;
	nb_philo = philo->nb_philo;
	ft_init_mutex(&mutex);
	while (i <= nb_philo - 1)
	{
		philo->mutex = mutex.mutex;
		philo->mutexprintf = mutex.mutexprintf;
		philo->mutexfork = mutex.mutexfork;
		philo->mutexdie = mutex.mutexdie;
		philo->mutexfinish = mutex.mutexfinish;
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
	ft_destroy_mutex(&mutex);
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
