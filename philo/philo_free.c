/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:46 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 11:00:55 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	destroy_philo_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_number)
	{
		if (&table->forks[i])
			pthread_mutex_destroy(&table->forks[i]);
	}
	if (table->forks)
		free(table->forks);
	if (table->philo)
		free(table->philo);
	table->philo = NULL;
	table->forks = NULL;
	pthread_mutex_destroy(&table->mutex_print);
	pthread_mutex_destroy(&table->mutex_wait);
}
