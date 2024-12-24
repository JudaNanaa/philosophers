/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:57:50 by madamou           #+#    #+#             */
/*   Updated: 2024/12/24 01:41:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_data data;
	t_philo	*philos;

	if (parse_args(argc, argv, &data) == 0)
		return (1);
	philos = init_philo(&data);
	ft_thread(philos, &data);
	free(philos);
	return (0);
}
