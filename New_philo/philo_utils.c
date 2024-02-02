/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:39:44 by mulken            #+#    #+#             */
/*   Updated: 2024/02/03 02:56:55 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

uint64_t	time_from_start(t_philo *philo)
{
	return (get_time_for_philo() - philo->start_time);
}

int	get_time_for_philo(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(u_int64_t t)
{
	u_int64_t	start;

	start = get_time_for_philo();
	while ((get_time_for_philo() - start) < t)
		usleep(t / 10);
	return (0);
}

void	print_philo(t_philo_data *philo_data, char *str, t_philo *philo)
{
	u_int64_t	time;

	time = time_from_start(philo);
	pthread_mutex_lock(&philo->print);
	pthread_mutex_lock(&philo->die_mutex);
	if (philo->is_dead == 1)
		printf("%llu %d %s\n", time, philo_data->id, str);
	pthread_mutex_unlock(&philo->die_mutex);
	pthread_mutex_unlock(&philo->print);
}

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
