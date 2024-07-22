/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:12:50 by madamou           #+#    #+#             */
/*   Updated: 2024/07/05 17:37:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <stdio.h>

t_philo	*ft_lstnew(int id, t_philo *philo)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->die = 0;
	new->nb_eat = philo->nb_eat;
	new->time_die = philo->time_die * 1000;
	new->time_eat = philo->time_eat * 1000;
	new->time_sleep = philo->time_sleep * 1000;
	new->nb_eat = philo->nb_eat;
	new->timestart = ft_time(philo, 2);
	if (new->timestart == 0)
		return (free(new), NULL);
	new->nb_philo = philo->nb_philo;
	new->before = NULL;
	new->next = NULL;
	return (new);
}

t_philo	*ft_add_back(t_philo *philos, t_philo *new)
{
	t_philo	*buff;

	buff = philos;
	if (!philos)
	{
		philos = new;
		new->before = NULL;
	}
	else
	{
		while (buff->next)
			buff = buff->next;
		buff->next = new;
		new->before = buff;
	}
	new->next = NULL;
	new->first = philos;
	philos->last = new;
	return (philos);
}

t_philo	*ft_clear_philos(t_philo *philos)
{
	t_philo	*buff;

	if (!philos)
		return (NULL);
	buff = philos->next;
	free(philos);
	return (ft_clear_philos(buff));
}

t_philo	*ft_init_struct(t_philo *philo)
{
	int		i;
	t_philo	*philos;
	t_philo	*new;

	i = 1;
	philos = NULL;
	while (i <= philo->nb_philo)
	{
		new = ft_lstnew(i, philo);
		if (!new)
			return (NULL);
		philos = ft_add_back(philos, new);
		i++;
	}
	philos->first->before = philos->last;
	return (philos);
}
