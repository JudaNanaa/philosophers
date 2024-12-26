/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:57:50 by madamou           #+#    #+#             */
/*   Updated: 2024/12/25 00:59:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_data data;
	t_philo	*philos;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(argc, argv, &data) == 0)
		return (1);
	philos = init_philo(&data);
	process(philos, &data);
	free(philos);
	return (0);
}
