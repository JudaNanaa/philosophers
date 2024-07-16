/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/16 14:38:03 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int	ft_init_mutex(t_mutex *mutex)
{
	pthread_mutex_t	*mutexprintf;
	pthread_mutex_t	*mutexdie;

	mutexprintf = malloc(sizeof(pthread_mutex_t));
	if (!mutexprintf)
	{
		printf("Error malloc mutex\n");
		return (-1);
	}
	mutexdie = malloc(sizeof(pthread_mutex_t));
	if (!mutexdie)
	{
		printf("Error malloc mutex\n");
		free(mutexprintf);
		return (-1);
	}
	pthread_mutex_init(mutexprintf, NULL);
	pthread_mutex_init(mutexdie, NULL);
	mutex->mutexprintf = mutexprintf;
	mutex->mutexdie = mutexdie;
	return (0);
}

void	ft_destroy_mutex(t_mutex *mutex, t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		pthread_mutex_destroy(philo->mutexfork);
		philo = philo->next;
	}
	free(tmp->first->mutexfork);
	pthread_mutex_destroy(mutex->mutexprintf);
	pthread_mutex_destroy(mutex->mutexdie);
}

int	ft_mutex_to_philo(t_mutex *mutex, t_philo *philo)
{
	pthread_mutex_t	*mutexfork;
	pthread_mutex_t	*mutex_nb_eat;
	t_philo			*buff;
	int				i;

	i = 0;
	buff = philo->first;
	mutexfork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!mutexfork)
		return (0);
	mutex_nb_eat = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!mutex_nb_eat)
		return (free(mutex_nb_eat), 0);
	while (philo)
	{
		pthread_mutex_init(&mutexfork[i], NULL);
		pthread_mutex_init(&mutex_nb_eat[i], NULL);
		philo->mutexprintf = mutex->mutexprintf;
		philo->mutex_nb_eat = &mutex_nb_eat[i];
		philo->mutexfork = &mutexfork[i++];
		philo->mutexdie = mutex->mutexdie;
		philo = philo->next;
	}
	philo = buff;
	return (1);
}

int	ft_creating_threads(t_philo *philo, pthread_t *threads)
{
	int		i;
	int		nb_philo;
	t_mutex	mutex;

	i = -1;
	nb_philo = philo->nb_philo;
	if (ft_init_mutex(&mutex) == -1 || ft_mutex_to_philo(&mutex, philo) == 0)
		return (0);
	pthread_mutex_lock(philo->mutexprintf);
	while (++i <= nb_philo - 1)
	{
		if (pthread_create(&threads[i], NULL, &ft_routine, philo) != 0)
			return (printf("Error creating threads %d\n", i), 0);
		philo = philo->before;
	}
	pthread_mutex_unlock(philo->mutexprintf);
	ft_main_thread(philo);
	i = -1;
	while (++i <= nb_philo - 1)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("Error waiting threads %d\n", i), 0);
	}
	return (ft_destroy_mutex(&mutex, philo), 1);
}

int	ft_thread(t_philo *philo)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	if (!threads)
		return (printf("Error malloc philos\n"), 0);
	if (ft_creating_threads(philo, threads) == 0)
		return (free(threads), 0);
	free(threads);
	return (1);
}
