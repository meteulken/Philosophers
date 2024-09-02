/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:38 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 12:28:21 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

u_int64_t	get_time_for_philo(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error\nCould not get time\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(u_int64_t time)
{
	size_t	start;

	start = get_time_for_philo();
	while ((get_time_for_philo() - start) < time)
		usleep(250);
}
