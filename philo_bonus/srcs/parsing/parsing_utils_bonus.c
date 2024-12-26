/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:36:31 by madamou           #+#    #+#             */
/*   Updated: 2024/12/25 00:41:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"
#include <stdio.h>

int	check_if_number(char **argv, int index)
{
	int	i;

	i = 0;
	while (argv[index][i])
	{
		if ((argv[index][i] < '0' || argv[index][i] > '9')
			&& (argv[index][i] != '-' && argv[index][i] != '+'))
			return (0);
		if (argv[index][i] == '-' || argv[index][i] == '+')
		{
			if (argv[index][i + 1] < '0' || argv[index][i + 1] > '9' || i != 0)
				return (0);
		}
		i++;
	}
	return (1);
}
