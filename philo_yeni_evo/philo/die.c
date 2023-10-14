/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:05:40 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:33:26 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	must_eat_check(t_table *table)
{
	int	i;

	if (table->number_of_must_eat < 0)
		return (0);
	i = -1;
	while (++i < table->number_of_philos)
	{
		if (table->philos[i].num_eat < table->number_of_must_eat)
			return (0);
	}
	return (1);
}

void	check_death(t_table *table)
{
	int	i;

	if (table->number_of_philos == 1)
	{
		print(table->philos, DIE);
	}
	while (table->number_of_philos > 1)
	{
		i = -1;
		while (++i < table->number_of_philos)
		{
			pthread_mutex_lock(&table->is_dying);
			if ((current_time() - table->philos[i].last_eat)
				>= table->time_to_die)
			{
				print(table->philos + i, DIE);
				table->stop = 1;
				return ;
			}
			pthread_mutex_unlock(&table->is_dying);
		}
		if (must_eat_check(table))
			break ;
	}
	table->stop = 1;
}
