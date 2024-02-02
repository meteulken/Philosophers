/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:39:44 by mulken            #+#    #+#             */
/*   Updated: 2024/02/02 12:42:29 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

uint64_t	time_from_start(t_philo *philo)
{
	return (get_time_for_philo() - philo->start_time);
}

int get_time_for_philo()
{
    struct timeval tv;
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

void print_philo(t_philo_data *philo_data, char *str, t_philo *philo)
{
	u_int64_t time;

	time = time_from_start(philo);
    pthread_mutex_lock(&philo->print);
	pthread_mutex_lock(&philo->die_mutex);
	if(philo->is_dead == 1)
    	printf("%llu %d %s\n", time, philo_data->id, str);
	pthread_mutex_unlock(&philo->die_mutex);
    pthread_mutex_unlock(&philo->print);
}

