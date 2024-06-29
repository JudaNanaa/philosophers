/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:57:50 by madamou           #+#    #+#             */
/*   Updated: 2024/06/29 08:18:58 by madamou          ###   ########.fr       */
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
	unsigned long long int test;
	struct timeval curent_time;

	if (ft_parse_args(argc, argv, &philo) == 0)
		return (1);
	if (gettimeofday(&curent_time, NULL) == -1)
		return (1);
	philos = ft_init_struct(&philo);
	ft_thread(philos);
	test = ((curent_time.tv_sec * 1000000) + curent_time.tv_usec) / 1000;
	printf("curent_time in microseconds is %lld\n", test);
	return (0);
}
