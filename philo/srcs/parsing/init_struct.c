/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:12:50 by madamou           #+#    #+#             */
/*   Updated: 2024/11/03 15:08:01 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>

void	ft_set_philos(t_philo *philo, int id, t_philo *data)
{
	philo->id = id;
	philo->die = 0;
	philo->nb_eat = data->nb_eat;
	philo->time_die = data->time_die * 1000;
	philo->time_eat = data->time_eat * 1000;
	philo->time_sleep = data->time_sleep * 1000;
	philo->nb_eat = data->nb_eat;
	philo->nb_philo = data->nb_philo;
}

t_philo	*ft_init_struct(t_philo *philo)
{
	int		i;
	t_philo	*philos;
	
	i = 0;
	philos = malloc(sizeof(t_philo) * philo->nb_philo);
	if (philos == NULL)
		return (NULL);
	while (i < philo->nb_philo)
	{
		ft_set_philos(&philos[i], i + 1, philo);
		philos[i].id = i + 1;
		i++;
	}
	return (philos);
}
