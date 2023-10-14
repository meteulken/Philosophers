/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:03:00 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:38:56 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*die_check(void *get_philo)
{
	t_philo	*philo;

	philo = (t_philo *)get_philo;
	while (1)
	{
		if (philo->table->number_of_philos == 1
			|| (current_time() - philo->last_eat) >= philo->table->time_to_die)
		{
			philo->table->stop = 1;
			print_dead(philo, DIE);
		}
		if (must_eat_check(philo->table))
			philo->table->stop = 1;
		if (philo->table->stop == 1)
			exit(1);
	}
	return (NULL);
}

void	_eat(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print(philo, TAKEN_FORK);
	sem_wait(philo->table->forks);
	print(philo, TAKEN_FORK);
	print(philo, IS_EATING);
	time_usleep(philo->table->time_to_eat);
	philo->last_eat = current_time();
	philo->num_eat++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	_sleep(t_philo *philo)
{
	print(philo, IS_SLEEPING);
	time_usleep(philo->table->time_to_sleep);
}

void	_think(t_philo *philo)
{
	print(philo, IS_THINKING);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	check;

	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_create(&check, NULL, die_check, philo);
	while (1)
	{
		_eat(philo);
		_sleep(philo);
		_think(philo);
	}
}
