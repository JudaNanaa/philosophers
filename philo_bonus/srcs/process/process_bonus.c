/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:36:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/10 05:31:53 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <semaphore.h>
#include <stdio.h>

int	ft_fork_create(pid_t *pid, t_philo *philo, int i)
{
	int	id;
	int	die;

	*pid = fork();
	if (*pid == -1)
		return (-1);
	if (*pid == 0)
	{
		free(&*pid - i);
		ft_routine(philo);
		id = philo->id;
		die = philo->die;
		ft_semaphore_close(philo);
		ft_clear_philos(philo->first);
		if (die == 0)
			exit(0);
		else
			exit(id);
	}
	return (0);
}

void	ft_kill(pid_t *pid, int nb_process)
{
	int	i;

	i = 0;
	while (i < nb_process)
	{
		if (pid[i] != 0)
			kill(pid[i], SIGKILL);
		i++;
	}
}

int	ft_fork_wait(t_philo *philo, pid_t *pid)
{
	static int				nb_wait;
	int						statut;
	unsigned long long int	time_death;

	time_death = 0;
	while (nb_wait < philo->nb_philo)
	{
		if (wait(&statut) == -1 && time_death == 0)
			return (-1);
		statut = statut / 256;
		if (statut != 0 && time_death == 0)
		{
			sem_wait(philo->sem_printf);
			time_death = ft_time(philo, 2);
			if (time_death == 0)
				return (sem_post(philo->sem_printf), -1);
			printf("%lld %d died\n", time_death / 1000, statut);
			break ;
		}
		nb_wait++;
	}
	ft_kill(pid, philo->nb_philo);
	return (0);
}

int	ft_creating_process(t_philo *philo, pid_t *pid)
{
	int		i;
	int		nb_philo;
	t_sema	semaphores;

	i = -1;
	nb_philo = philo->nb_philo;
	if (ft_init_semaphores(&semaphores) == -1)
		return (0);
	if (ft_semaphore_to_philo(&semaphores, philo) == -1)
		return (ft_semaphore_close(philo), 0);
	sem_wait(semaphores.sem_print);
	while (++i <= nb_philo - 1)
	{
		if (ft_fork_create(&pid[i], philo, i) != 0)
			return (printf("Error creating forks %d\n", i), 0);
		philo = philo->before;
	}
	sem_post(semaphores.sem_print);
	if (ft_fork_wait(philo, pid) == -1)
		return (ft_semaphore_close(philo), 0);
	sem_post(semaphores.sem_print);
	return (ft_semaphore_close(philo), 1);
}

int	ft_thread(t_philo *philo)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * philo->nb_philo);
	if (!pid)
		return (printf("Error malloc philos\n"), 0);
	if (ft_creating_process(philo, pid) == 0)
		return (free(pid), 0);
	free(pid);
	return (1);
}
