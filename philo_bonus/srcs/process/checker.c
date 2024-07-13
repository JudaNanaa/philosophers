/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:02:48 by madamou           #+#    #+#             */
/*   Updated: 2024/07/13 06:13:23 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	ft_get_or_set_kill_value(t_checker *checker, int cas)
{
	int	result;

	result = 0;
	sem_wait(checker->sem_kill);
	if (cas == 1)
		result = *checker->kill;
	if (cas == 2)
		*checker->kill = 1;
	sem_post(checker->sem_kill);
	return (result);
}

t_checker	*ft_checker_in_static(t_checker *checker, int cas)
{
	static t_checker	*stat;

	if (cas == 1)
		stat = checker;
	return (stat);
}

t_checker	*ft_init_checker(t_philo *philo, pid_t *pid, int i)
{
	sem_t		*kill;
	int			*dead;
	t_checker	*checker;

	checker = malloc(sizeof(t_checker) * philo->nb_philo);
	if (!checker)
		return (NULL);
	kill = sem_open("kill", O_CREAT, 0600, 0);
	if (kill == SEM_FAILED)
		return (printf("Error open semaphore checker\n"), free(checker), NULL);
	dead = malloc(sizeof(int));
	if (!dead)
		return (free(checker), sem_close(kill), NULL);
	*dead = 0;
	while (i < philo->nb_philo)
	{
		checker[i].nb_philo = philo->nb_philo;
		checker[i].pid = pid;
		checker[i].kill = dead;
		checker[i].sem_kill = kill;
		checker[i].philo = philo;
		checker[i].first = &checker[0];
		i++;
	}
	return (sem_post(kill), checker);
}

void	*ft_routine_threads(void *args)
{
	int				status;
	t_checker		*checker;
	long long int	time_death;

	checker = (t_checker *)args;
	status = 0;
	if (waitpid(checker->pid[checker->i], &status, 0) == -1)
		return (NULL);
	status = status / 256;
	if (status != 0 && ft_get_or_set_kill_value(checker, 1) == 0)
	{
		ft_get_or_set_kill_value(checker, 2);
		sem_wait(checker->philo->sem_printf);
		time_death = ft_time(checker->philo, 2);
		if (time_death == 0)
			return (sem_post(checker->philo->sem_printf), NULL);
		printf("%lld %d died\n", time_death / 1000, status);
		ft_kill(checker);
		sem_post(checker->philo->sem_printf);
		ft_checker_in_static(checker->first, 1);
	}
	return (NULL);
}

int	ft_create_threads(t_philo *philo, pthread_t *threads, pid_t *pid)
{
	int			i;
	int			nb_philos;
	t_checker	*checker;

	i = 0;
	checker = ft_init_checker(philo, pid, 0);
	nb_philos = philo->nb_philo;
	while (i < nb_philos)
	{
		checker[i].i = i;
		if (pthread_create(&threads[i], NULL, ft_routine_threads,
				&checker[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
