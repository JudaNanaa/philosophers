/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:57:50 by madamou           #+#    #+#             */
/*   Updated: 2024/07/02 10:07:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	t_philo philo;
	t_philo *philos;

	if (ft_parse_args(argc, argv, &philo) == 0)
		return (1);
	philos = ft_init_struct(&philo);
	ft_thread(philos);
	ft_clear_philos(philos);
	return (0);
}
