/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:54 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 11:57:48 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	init_philo(t_table *table)
{
	int	i;

	table->philo = (t_philo *)ft_calloc(table->philo_number, sizeof(t_philo));
	if (!table->philo)
		return (printf("%s\n", "Error\nMemory allocation failed\n"), 1);
	i = 0;
	table->start = get_time_for_philo();
	while (i < table->philo_number)
	{
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->philo_number;
		table->philo[i].p_id = i + 1;
		table->philo[i].table = table;
		table->philo[i].last_eat = table->start;
		i++;
	}
	return (0);
}

int	create_mutex(t_table *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)ft_calloc(table->philo_number,
			sizeof(pthread_mutex_t));
	if (!table->forks)
		return (printf("Error\nMemory allocation failed\n"), 1);
	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (printf("Error\nCould not create mutex\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&table->mutex_print, NULL) != 0)
		return (printf("Error\nCould not create mutex\n"), 1);
	if (pthread_mutex_init(&table->mutex_wait, NULL) != 0)
		return (printf("Error\nCould not create mutex\n"), 1);
	table->check_die = 0;
	table->eat_count = 0;
	return (0);
}
