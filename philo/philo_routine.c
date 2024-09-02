/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:59:43 by mulken            #+#    #+#             */
/*   Updated: 2024/09/02 11:46:14 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	mutex_unlock(t_table *table, t_philo *philo, int flag)
{
	if (flag == 0)
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
	else if (flag == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
	}
}

int	eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	if (print_philo("left forks", philo) == 1)
		return (mutex_unlock(table, philo, 0), 1);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	if (print_philo("right forks", philo) == 1)
		return (mutex_unlock(table, philo, 1), 1);
	if (print_philo("is eating", philo) == 1)
		return (mutex_unlock(table, philo, 1), 1);
	ft_usleep(table->time_to_eat);
	pthread_mutex_lock(&table->mutex_print);
	philo->last_eat = get_time_for_philo();
	pthread_mutex_unlock(&table->mutex_print);
	mutex_unlock(table, philo, 1);
	philo->eat_count++;
	return (0);
}

int	philo_cycle(t_philo *philo, t_table *table)
{
	if (eating(philo, table) == 1)
		return (1);
	if (print_philo("is sleeping", philo) == 1)
		return (1);
	ft_usleep(philo->table->time_to_sleep);
	if (print_philo("is thiking", philo) == 1)
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->p_id % 2 == 0)
		ft_usleep(10);
	while (philo_cycle(philo, philo->table) == 0)
	{
		pthread_mutex_lock(&philo->table->mutex_wait);
		if (philo->eat_count == philo->table->eat_limit)
		{
			philo->table->eat_count++;
			pthread_mutex_unlock(&philo->table->mutex_wait);
			break ;
		}
		pthread_mutex_unlock(&philo->table->mutex_wait);
	}
	return (NULL);
}

int	start_philo(t_table *table, int i)
{
	while (++i < table->philo_number)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_routine,
				&table->philo[i]) != 0)
			return (printf("Error\nCould not create thread\n"), 1);
	}
	while (1)
	{
		i = -1;
		while (++i < table->philo_number)
		{
			pthread_mutex_lock(&table->mutex_wait);
			if (die_control(table, &table->philo[i], i) == 1
				|| table->eat_count == table->philo_number)
			{
				pthread_mutex_unlock(&table->mutex_wait);
				break ;
			}
			pthread_mutex_unlock(&table->mutex_wait);
		}
		if (i != table->philo_number)
			break ;
	}
	return (0);
}
