/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 02:27:39 by madamou           #+#    #+#             */
/*   Updated: 2024/07/10 05:32:34 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static int	ft_size_malloc(long nb)
{
	int	size;

	size = 1;
	if (nb < 0)
	{
		nb = -nb;
		size++;
	}
	while (nb / 10 > 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

static void	ft_norminette(char *result, long nb, int size)
{
	if (nb < 0)
	{
		nb = -nb;
		result[0] = '-';
	}
	if (nb >= 10)
	{
		ft_norminette(result, nb / 10, size - 1);
		ft_norminette(result, nb % 10, size);
	}
	if (nb < 10)
	{
		result[size - 1] = (nb + '0');
	}
}

char	*ft_itoa(int n)
{
	long	nb;
	int		size;
	char	*result;

	nb = n;
	size = ft_size_malloc(nb);
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	ft_norminette(result, nb, size);
	result[size] = '\0';
	return (result);
}
