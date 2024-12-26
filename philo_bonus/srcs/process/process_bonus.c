/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:40:51 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:21:55 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

int	childs_create(t_philo *philo)
{
	philo->pid = fork();
	if (philo->pid == -1)
		return (-1);
	if (philo->pid == 0)
	{
		routine(philo);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	wait_childs(t_philo *philo)
{
	int i;
	int nb_philos;

	i = 0;
	nb_philos = philo->data->nb_philo;	
	while (i < nb_philos)
	{
		waitpid(philo->pid, NULL, 0);
		i++;
	}
}

int	process(t_philo *philo, t_data *data)
{
	int				i;
	int				nb_philo;
	long long int	time_start;

	i = 0;
	nb_philo = data->nb_philo;
	time_start = get_time();
	if (time_start == 0)
		return (EXIT_FAILURE);
	data->time_start = time_start;
	while (i < nb_philo)
	{
		philo[i].last_meal = time_start;
		if (childs_create(&philo[i]) != 0)
			return (printf("Error creating forks %d\n", i), EXIT_FAILURE);
		i++;
	}
	wait_childs(philo);
	semaphore_close(data);
	return (EXIT_SUCCESS);
}
