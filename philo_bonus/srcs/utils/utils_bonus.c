/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:10:23 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:01:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

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

long long	get_time(void)
{
	long long int	nb;
	struct timeval			time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	nb = ((time.tv_sec * 1000000) + time.tv_usec);
	return (nb);
}
