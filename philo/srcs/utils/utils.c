/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:10:23 by madamou           #+#    #+#             */
/*   Updated: 2024/07/22 05:17:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <bits/types/struct_timeval.h>

long	ft_atol(char *str)
{
	long	result;
	int		i;
	long	sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

unsigned long long int	ft_time(t_philo *philo, int cas)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	if (cas == 1)
		philo->timestart = ((time.tv_sec * 1000000) + time.tv_usec);
	return (((time.tv_sec * 1000000) + time.tv_usec));
}
