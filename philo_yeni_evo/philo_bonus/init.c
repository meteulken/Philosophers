/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:02:27 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:38:35 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	must_eat_check(t_table *table)
{
	int	i;

	if (table->number_of_must_eat < 0)
		return (0);
	i = -1;
	while (++i < table->number_of_philos)
	{
		if ((table->philos[i].num_eat == table->number_of_must_eat)
			&& table->philos[i].id % 2 == 0)
			return (1);
	}
	return (0);
}

void	philo_init(t_philo *philo, t_table *table, int i)
{
	philo->id = i + 1;
	philo->table = table;
	philo->num_eat = 0;
	philo->last_eat = current_time();
}

void	init_sem(t_table *table)
{
	sem_unlink("./forks");
	sem_unlink("./printing");
	sem_unlink("./dying");
	table->forks = sem_open("./forks", O_CREAT, 0666,
			table->number_of_philos);
	table->is_printing = sem_open("./printing", O_CREAT, 0666, 1);
	table->is_dying = sem_open("./dying", O_CREAT, 0666, 1);
}

void	start_forks(t_table *table)
{
	int	i;
	int	response;

	init_sem(table);
	i = -1;
	while (++i < table->number_of_philos)
		philo_init(&table->philos[i], table, i);
	i = -1;
	while (++i < table->number_of_philos)
	{
		table->philos[i].child = fork();
		if (table->philos[i].child == 0)
			philo_routine(table->philos + i);
	}
	waitpid(-1, &response, 0);
	i = -1;
	while (++i < table->number_of_philos)
		kill (table->philos[i].child, SIGKILL);
}
