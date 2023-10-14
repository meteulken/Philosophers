/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:05:49 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:33:36 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo, t_table *table, int i)
{
	philo->id = i + 1;
	philo->table = table;
	philo->num_eat = 0;
	philo->last_eat = current_time();
	pthread_mutex_init(table->forks + i, NULL);
}

void	fork_init(t_philo *philo, t_table *table, int i)
{
	if (i - 1 < 0)
		philo->right_fork = table->forks + (table->number_of_philos - 1);
	else
		philo->right_fork = table->forks + (i - 1);
	philo->left_fork = table->forks + i;
}

void	creating_threads(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->is_dying, NULL);
	pthread_mutex_init(&table->is_printing, NULL);
	i = -1;
	while (++i < table->number_of_philos)
		philo_init(table->philos + i, table, i);
	i = -1;
	while (++i < table->number_of_philos)
		fork_init(table->philos + i, table, i);
	i = -1;
	while (++i < table->number_of_philos)
		pthread_create(&table->philos[i].thread, NULL,
			routine, table->philos + i);
	check_death(table);
}
