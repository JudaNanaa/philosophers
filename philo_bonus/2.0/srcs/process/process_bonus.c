/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:40:51 by madamou           #+#    #+#             */
/*   Updated: 2024/07/23 17:08:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_fork_create(pid_t *pid, t_philo *philo, int i)
{
	*pid = fork();
	if (*pid == -1)
		return (-1);
	if (*pid == 0)
	{
		free(&*pid - i);
 		ft_routine(philo);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	ft_kill(pid_t *pid, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pid[i] != 0)
			kill(pid[i], SIGKILL);
		i++;
	}
}

int ft_creating_checkers(t_sema *sem, int nb_philo, pid_t *pid, t_philo *philo)
{
	pid_t pid_finish;
	pid_t die;
	int nb_finish;

	nb_finish = 0;
	die = fork();
	if (die == -1)
		return (-1);
	if (die == 0)
	{
		sem_wait(sem->sem_die);
		(ft_kill(pid, nb_philo), free(pid));
		sem_post(sem->sem_print);
		(ft_semaphore_close(philo), ft_clear_philos(philo));
		exit(EXIT_SUCCESS);
	}
	pid_finish = fork();
	if (pid_finish == -1)
		return (-1);
	if (pid_finish == 0)
	{
		while (nb_finish++ < nb_philo)
			sem_wait(sem->sem_finish);
		(ft_kill(pid, nb_philo), free(pid));
		sem_post(sem->sem_die);
		(ft_semaphore_close(philo), ft_clear_philos(philo));
		exit(EXIT_SUCCESS);
	}
	if (waitpid(die, NULL, 0) == -1)
		return (-1);
	kill(pid_finish, SIGKILL);
	return (0);
}

int	ft_creating_process(t_philo *philo, pid_t *pid)
{
	int		i;
	int		nb_philo;
	t_sema	semaphores;
	unsigned long long int	time;

	i = -1;
	nb_philo = philo->nb_philo;
	if (ft_init_semaphores(&semaphores, philo) == -1)
		return (0);
	time = ft_time(philo, 2);
	if (time == 0)
		return (-1);
	if (ft_semaphore_to_philo(&semaphores, philo) == -1)
		return (0);
	while (++i <= nb_philo - 1)
	{
		philo->timestamp = time;
		if (ft_fork_create(&pid[i], philo, i) != 0)
			return (printf("Error creating forks %d\n", i), 0);
		philo = philo->before;
	}
	if (ft_creating_checkers(&semaphores, nb_philo, pid, philo) == -1)
		return (ft_semaphore_close(philo), 0);
	return (ft_semaphore_close(philo), 1);
}

int	ft_process(t_philo *philo)
{
	pid_t		*pid;

	pid = malloc(sizeof(pid_t) * philo->nb_philo);
	if (!pid)
		return (printf("Error malloc philos\n"), 0);
	if (ft_creating_process(philo, pid) == 0)
		return (free(pid), 0);
	free(pid);
	return (1);
}
