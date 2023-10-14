/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:02:39 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:38:40 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_ps(t_table *table)
{
	sem_close(table->is_dying);
	sem_close(table->is_printing);
	sem_close(table->forks);
	sem_unlink("./forks");
	sem_unlink("./printing");
	sem_unlink("./dying");
	free(table->philos);
	free(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = parse(ac, av);
	if (table != NULL)
	{
		start_forks(table);
		end_ps(table);
	}
	return (0);
}
