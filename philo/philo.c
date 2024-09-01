/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:23:58 by mulken            #+#    #+#             */
/*   Updated: 2024/02/27 14:36:32 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	philo_eat(t_philo_data *philo_data)
{
	if (philo_data->philo->eat_count != -1 && \
	philo_data->eat_count >= philo_data->philo->eat_count)
		return ;
	pthread_mutex_lock(philo_data->right_fork);
	print_philo(philo_data, "has taken a fork", philo_data->philo);
	pthread_mutex_lock(philo_data->left_fork);
	print_philo(philo_data, "has taken a fork", philo_data->philo);
	print_philo(philo_data, "is eating", philo_data->philo);
	pthread_mutex_lock(&philo_data->philo->eat);
	philo_data->eat_count++;
	philo_data->time_to_start = get_time_for_philo();
	pthread_mutex_unlock(&philo_data->philo->eat);
	ft_usleep(philo_data->philo->time_to_eat);
	pthread_mutex_unlock(philo_data->left_fork);
	pthread_mutex_unlock(philo_data->right_fork);
}

void	philo_sleep_think(t_philo_data *philo_data)
{	
	pthread_mutex_lock(&philo_data->philo->sleep);
	print_philo(philo_data, "is sleeping", philo_data->philo);
	ft_usleep(philo_data->philo->time_to_sleep);
	print_philo(philo_data, "is thinking", philo_data->philo);
	pthread_mutex_unlock(&philo_data->philo->sleep);
}
#include <stdio.h>
void	*philo_routine(void *arg)
{
	t_philo_data	*philo_data;
	int				check;

	philo_data = (t_philo_data *)arg;
	if (philo_data->philo->num_of_philo == 1)
	{
		pthread_mutex_lock(philo_data->right_fork);
		print_philo(philo_data, "has taken a fork", philo_data->philo);
		return (NULL);
	}
	check = 1;
	if (philo_data->id % 2 == 0)
		ft_usleep(10);
	while (check)
	{
		pthread_mutex_lock(&philo_data->philo->die_mutex);
		check = philo_data->philo->is_dead;
		pthread_mutex_unlock(&philo_data->philo->die_mutex);
		if (check == 0)
		{
			break ;
		}
		philo_eat(philo_data);
		philo_sleep_think(philo_data);
	}
	return (NULL);
}

int	start_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_create(&philo->philo_data[i].thread, NULL, \
		&philo_routine, &philo->philo_data[i]);
		i++;
	}
	if (philo_die_control(philo) == 0)
	{
		pthread_mutex_lock(&philo->die_mutex);
		philo->philo_data->philo->is_dead = 0;
		pthread_mutex_unlock(&philo->die_mutex);
	}
	return (-1);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;

	if (argc > 6 || argc < 5 || ft_atoi(argv[1]) < 1)
		return (write(1, "Error: Wrong arguments\n", 24), 1);
	if (argument_control(argv))
		return (write(1, "Error: Arguments must be positive numbers\n", 42), 1);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (write(1, "Error: t_philo allocation error\n", 32), 1);
	philo->mc = malloc_start();
	if (!philo->mc)
		return (free(philo), 1);
	init_philo(philo, argv, argc);
	philo->philo_data = (t_philo_data *)new_malloc(philo->mc, \
	sizeof(t_philo_data) * philo->num_of_philo);
	if (!philo->philo_data)
		return (end_malloc(philo->mc), free(philo), 1);
	philo->forks = (pthread_mutex_t *)new_malloc(philo->mc, \
	sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (!philo->forks)
		return (end_malloc(philo->mc), free(philo), 1);
	if (init_philo_data(philo) == -1)
		return (philo_die_all(philo), end_malloc(philo->mc), free(philo), 1);
	return (end_malloc(philo->mc), free(philo), 0);
}
