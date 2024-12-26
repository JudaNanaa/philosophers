/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 05:20:51 by madamou           #+#    #+#             */
/*   Updated: 2024/12/26 10:22:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

void	semaphore_close(t_data *data)
{
	if (sem_close(data->sema_fork) == -1)
		printf("Error when close semaphore fork\n");
	if (sem_close(data->sema_printf) == -1)
		printf("Error when close semaphore printf\n");
	if (sem_close(data->sema_taking_fork) == -1)
		printf("Error when close semaphore taking fork\n");
	if (sem_close(data->sema_die) == -1)
		printf("Error when close semaphore die\n");
}
