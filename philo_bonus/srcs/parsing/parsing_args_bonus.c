/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:16:09 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 20:47:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <stdio.h>
#include <strings.h>

int	ft_verify_if_good(t_philo *data, char **argv)
{
	int	cpt;

	cpt = 0;
	data->nb_philo = ft_atol(argv[1]);
	if (data->nb_philo <= 0)
		(printf("%ld not good for nb of philo\n", data->nb_philo), cpt++);
	data->time_die = ft_atol(argv[2]);
	if (data->time_die < 0)
		(printf("%lld not good for time to die\n", data->time_die), cpt++);
	data->time_eat = ft_atol(argv[3]);
	if (data->time_eat < 0)
		(printf("%ld not good for time to eat\n", data->time_eat), cpt++);
	data->time_sleep = ft_atol(argv[4]);
	if (data->time_sleep < 0)
		(printf("%ld not good for time to sleep\n", data->time_sleep), cpt++);
	return (cpt);
}

int	ft_verify_if_number(char **argv)
{
	int	index;
	int	cpt;

	cpt = 0;
	index = 1;
	while (argv[index])
	{
		if (ft_check_if_number(argv, index) == 0)
		{
			printf("Error argument %d is not a number\n", index + 1);
			cpt++;
		}
		index++;
	}
	if (cpt != 0)
		return (-1);
	return (0);
}

int	ft_parse_args(int argc, char **argv, t_philo *data)
{
	if (argc < 5 || argc > 6)
		return (printf("Error number of arguments\n"), 0);
	if (ft_verify_if_number(argv) == -1)
		return (0);
	if (ft_verify_if_good(data, argv) != 0)
		return (0);
	if (argv[5] != NULL)
	{
		data->nb_eat = ft_atol(argv[5]);
		if (data->nb_eat < 0)
			return (printf("%ld not good for nb philo must eat\n",
					data->nb_eat), 0);
	}
	else
		data->nb_eat = -1;
	return (1);
}
