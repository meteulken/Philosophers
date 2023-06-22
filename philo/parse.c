/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:20:27 by mulken            #+#    #+#             */
/*   Updated: 2023/06/13 13:20:30 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (err_msg("Number of arguments must be 4 or 5.\n"));
	if (unsigned_atoi(av[1]) <= 0)
		return (err_msg("Number of philos must be bigger than 0.\n"));
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (err_msg("Arguments must be digit.\n"));
		i++;
	}
	return (1);
}

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	if (!valid_check(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_of_philos = unsigned_atoi(av[1]);
	table->time_to_die = unsigned_atoi(av[2]);
	table->time_to_eat = unsigned_atoi(av[3]);
	table->time_to_sleep = unsigned_atoi(av[4]);
	table->number_of_must_eat = -1;
	if (ac == 6)
		table->number_of_must_eat = unsigned_atoi(av[5]);
	table->philos = malloc(sizeof(t_philo) * table->number_of_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philos);
	table->time = current_time();
	table->stop = 0;
	return (table);
}
