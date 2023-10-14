/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:06:23 by mulken            #+#    #+#             */
/*   Updated: 2023/10/14 12:37:29 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->left_fork);
	print(philo, TAKEN_FORK);
	philo->num_eat++;
	print(philo, IS_EATING);
	time_usleep(philo->table->time_to_eat);
	philo->last_eat = current_time();
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	print(philo, IS_SLEEPING);
	time_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print(philo, IS_THINKING);
}

void	*routine(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->id % 2 == 0)
		time_usleep(10);
	while (!philo->table->stop)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
