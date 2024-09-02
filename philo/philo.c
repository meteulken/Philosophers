/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:11 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 10:59:52 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	waiting_processes(t_table *table, int i)
{
	if (start_philo(table, -1) == 1)
		return (1);
	while (++i < table->philo_number)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (printf("Error\nThread waiting not be done\n"), 1);
	}
	if (table->check_die)
		printf("%llu	Philo: %d  %s\n", table->die_time, table->die_id,
			"is died");
	return (0);
}

void	*just_one_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_philo("left forks", philo);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	ft_usleep(philo->table->time_to_die);
	print_philo("is died", philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (argument_control(ac, av, &table) == 1)
		return (1);
	if (init_philo(&table) == 1)
		return (1);
	if (create_mutex(&table) == 1)
		return (destroy_philo_forks(&table), 1);
	if (table.philo_number == 1)
	{
		if (pthread_create(&table.philo[0].thread, NULL, &just_one_philo,
				&table.philo[0]) != 0)
			return (printf("Error\nCould not create thread\n"), \
			destroy_philo_forks(&table), 1);
		if (pthread_join(table.philo[0].thread, NULL) != 0)
			return (printf("Error\nCould not create thread\n"), \
			destroy_philo_forks(&table), 1);
		return (destroy_philo_forks(&table), 0);
	}
	if (waiting_processes(&table, -1) == 1)
		return (destroy_philo_forks(&table), 1);
	return (destroy_philo_forks(&table), 0);
}
