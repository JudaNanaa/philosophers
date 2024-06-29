/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/06/29 20:01:19 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <unistd.h>

extern int usleep (__useconds_t __useconds);

void ft_mutex(t_philo *philo)
{
	struct timeval curent_time;
	unsigned long long int test;

	if (philo->id != 1 && philo->id != philo->nb_philo)
	{
		if (philo->fork == 1 && philo->before->fork == 1)
		{
			pthread_mutex_lock(&philo->mutex);
			philo->fork = 0;
			philo->before->fork = 0;
			gettimeofday(&curent_time, NULL);
			test = ((curent_time.tv_sec * 1000000) + curent_time.tv_usec) / 1000;
			printf("%lld %d is eating\n", test, philo->id);
			usleep(philo->time_eat * 1000);
			philo->fork = 1;
			philo->before->fork = 1;
			pthread_mutex_unlock(&philo->mutex);
		}
	}
}

void *ft_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	ft_mutex(philo);
	return (NULL);
}

int ft_creating_threads(t_philo *philo, pthread_t *threads)
{
	int i;
	int nb_philo;
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	nb_philo = philo->nb_philo;
	while (i <= nb_philo - 1)
	{
		philo->mutex = mutex;
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
