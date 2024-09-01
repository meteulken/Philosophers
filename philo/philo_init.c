/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:09:39 by mulken            #+#    #+#             */
/*   Updated: 2024/02/05 18:07:09 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_data(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
		{
			break ;
		}
		i++;
	}
	if (philo->num_of_philo != i)
		return (destroy_philo_forks(philo, i));
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->philo_data[i].left_fork = &philo->forks[i];
		philo->philo_data[i].right_fork = \
		&philo->forks[(i + 1) % philo->num_of_philo];
		i++;
	}
	return (init_philo_mutex(philo));
}

int	init_philo(t_philo *philo, char *argv[], int argc)
{
	philo->num_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_count = ft_atoi(argv[5]);
	else
		philo->eat_count = -1;
	philo->start_time = get_time_for_philo();
	philo->is_dead = 1;
	philo->is_eating = 0;
	return (0);
}

int	philo_mutex_destroy(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	if (count > 1)
		pthread_mutex_destroy(&philo->print);
	else if (count > 2)
		pthread_mutex_destroy(&philo->eat);
	else if (count > 3)
		pthread_mutex_destroy(&philo->sleep);
	else if (count > 4)
		pthread_mutex_destroy(&philo->die);
	else if (count > 5)
		pthread_mutex_destroy(&philo->die_mutex);
	return (-2);
}

int	init_philo_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	if (i++, (pthread_mutex_init(&philo->print, NULL) != 0))
		return (philo_mutex_destroy(philo, i));
	if (i++, (pthread_mutex_init(&philo->eat, NULL) != 0))
		return (philo_mutex_destroy(philo, i));
	if (i++, (pthread_mutex_init(&philo->sleep, NULL) != 0))
		return (philo_mutex_destroy(philo, i));
	if (i++, (pthread_mutex_init(&philo->die, NULL) != 0))
		return (philo_mutex_destroy(philo, i));
	if (i++, (pthread_mutex_init(&philo->die_mutex, NULL) != 0))
		return (philo_mutex_destroy(philo, i));
	return (init_philo_data_helper(philo));
}

int	init_philo_data_helper(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->philo_data[i].philo = philo;
		philo->philo_data[i].id = i + 1;
		philo->philo_data[i].time_to_start = get_time_for_philo();
		philo->philo_data[i].eat_count = 0;
		i++;
	}
	return (start_philo(philo));
}
