/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_arg_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:58 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 11:47:10 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	argument_msg(t_table *table)
{
	if (!table->philo_number)
		printf("%s\n", "Error\nThere is a mistake in number of philosophers");
	if (!table->time_to_die)
		printf("%s\n", "Error\nThere is a mistake in time to die");
	if (!table->time_to_eat)
		printf("%s\n", "Error\nThere is a mistake in time to eat");
	if (!table->time_to_sleep)
		printf("%s\n", "Error\nThere is a mistake in time to sleep");
	if (!table->eat_limit)
		printf("%s\n", "Error\nThere is a mistake in number of times \
		each philosopher must eat");
}

static int	philo_init(int ac, char **av, t_table *table)
{
	if (ac == 5 || ac == 6)
	{
		table->philo_number = ft_philo_atoi(av[1]);
		table->time_to_die = ft_philo_atoi(av[2]);
		table->time_to_eat = ft_philo_atoi(av[3]);
		table->time_to_sleep = ft_philo_atoi(av[4]);
		if (ac == 6)
			table->eat_limit = ft_philo_atoi(av[5]);
		else
			table->eat_limit = -1;
		return (0);
	}
	return (1);
}

int	argument_control(int ac, char **av, t_table *table)
{
	if (philo_init(ac, av, table) == 1)
		return (printf("%s\n", "Error\n./philo philosophers time_to_die " \
		"time_to_eat time_to_sleep [must_eat]"), 1);
	else
	{
		argument_msg(table);
		if (!table->philo_number || !table->time_to_die || !table->time_to_eat
			|| !table->time_to_sleep || !table->eat_limit)
			return (1);
	}
	return (0);
}
