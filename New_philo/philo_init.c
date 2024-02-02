/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:09:39 by mulken            #+#    #+#             */
/*   Updated: 2024/02/02 15:55:11 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo_data(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->num_of_philo)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
        {
            return -1;
        }
        i++;
    }
    i = 0;
    while (i < philo->num_of_philo)
    {
        philo->philo_data[i].left_fork = &philo->forks[i];
        philo->philo_data[i].right_fork = &philo->forks[(i + 1) % philo->num_of_philo];
        i++;
    }
    return (init_philo_mutex(philo));
}

int init_philo(t_philo *philo, char *argv[], int argc)
{
    philo->num_of_philo = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if(argc == 6)
        philo->eat_count = ft_atoi(argv[5]);
    else
        philo->eat_count = -1;
    philo->start_time = get_time_for_philo();
    philo->is_dead = 1;
    philo->is_eating = 0;
    philo->is_sleeping = 0;
    philo->is_thinking = 0;
    return (0);
}


int init_philo_mutex(t_philo *philo)
{
    pthread_mutex_init(&philo->print, NULL);
    pthread_mutex_init(&philo->eat, NULL);
    pthread_mutex_init(&philo->sleep, NULL);
    pthread_mutex_init(&philo->think, NULL);
    pthread_mutex_init(&philo->die, NULL);
    pthread_mutex_init(&philo->die_mutex, NULL);
    pthread_mutex_init(&philo->eat_last, NULL);
    return (init_philo_data_helper(philo));
}

int init_philo_data_helper(t_philo *philo)
{
    int i = 0;
    while(i < philo->num_of_philo)
    {
        philo->philo_data[i].philo = philo;
        philo->philo_data[i].id = i + 1;
        philo->philo_data[i].time_to_start = get_time_for_philo();
        philo->philo_data[i].eat_count = 0;
        i++;
    }
    return (start_philo(philo));
}
