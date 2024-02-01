/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:57:42 by mulken            #+#    #+#             */
/*   Updated: 2024/02/01 07:57:45 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	indx;
	int	ret;
	int	sign;

	indx = 0;
	ret = 0;
	sign = 1;
	while (nptr[indx] == ' ' || (nptr[indx] >= 9 && nptr[indx] <= 13))
		indx++;
	if (nptr[indx] == '+' || nptr[indx] == '-')
	{
		if (nptr[indx] == '-')
			sign *= -1;
		indx++;
	}
	while (nptr[indx] >= '0' && nptr[indx] <= '9')
	{
		ret = nptr[indx] - 48 + ret * 10;
		indx++;
	}
	return ((ret * sign));
}