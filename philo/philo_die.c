/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:50 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 11:45:39 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	print_philo(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex_print);
	if (philo->table->check_die != 1)
	{
		printf("%llu	Philo: %d  %s\n", \
		get_time_for_philo() - philo->table->start,
			philo->p_id, str);
		pthread_mutex_unlock(&philo->table->mutex_print);
		return (0);
	}
	return (pthread_mutex_unlock(&philo->table->mutex_print), 1);
}

int	die_control(t_table *table, t_philo *philo, int i)
{
	pthread_mutex_lock(&table->mutex_print);
	if ((get_time_for_philo() - philo->last_eat) > table->time_to_die)
	{
		table->check_die = 1;
		table->die_id = i + 1;
		table->die_time = get_time_for_philo() - table->start;
		pthread_mutex_unlock(&table->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(&table->mutex_print);
	return (0);
}
