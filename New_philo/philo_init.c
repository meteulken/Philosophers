/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:09:39 by mulken            #+#    #+#             */
/*   Updated: 2024/01/30 14:24:46 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo_data(t_philo *philo)
{
    int i;

    i = 0;
    philo->forks = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t) * philo->num_of_philo);
    //printf("forks init\n");
    //pthread_mutex_init(philo->die, NULL);
    while(i < philo->num_of_philo)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
        {
            return 1;
        }
        i++;   
    }
    i = 1;
    philo->philo_data = (t_philo_data *)new_malloc(philo->mc, sizeof(t_philo_data) * philo->num_of_philo);
    /*
    philo->philo_data[0].left_fork = &philo->forks[philo->num_of_philo - 1];
    philo->philo_data[0].right_fork = &philo->forks[0];
    while (i < philo->num_of_philo)
    {
        philo->philo_data[i].left_fork = &philo->forks[i];
        philo->philo_data[i].right_fork = &philo->forks[i + 1];
        i++;
    }
    */
   philo->philo_data[i].left_fork = &philo->forks[0];
   philo->philo_data[i].right_fork = &philo->forks[philo->num_of_philo - 1];
    while(i < philo->num_of_philo)
    {
        philo->philo_data[i].left_fork = &philo->forks[i];
        philo->philo_data[i].right_fork = &philo->forks[i - 1];
        i++;
    }
    //printf("philo_data init\n");
    return 0;
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

int init_philo_data_mutex(t_philo_data *philo_data)
{
    philo_data->print = (pthread_mutex_t *)new_malloc(philo_data->philo->mc, sizeof(pthread_mutex_t));
    pthread_mutex_init(philo_data->print, NULL);
    return (0);
}

int init_philo_mutex(t_philo *philo)
{
    philo->print = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t));
    philo->eat = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t));
    philo->sleep = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t));
    philo->think = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t));
    philo->die = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t));
    //philo->philo_data->print = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t));
    pthread_mutex_init(philo->print, NULL);
    pthread_mutex_init(philo->eat, NULL);
    pthread_mutex_init(philo->sleep, NULL);
    pthread_mutex_init(philo->think, NULL);
    pthread_mutex_init(philo->die, NULL);
    pthread_mutex_init(&philo->die_mutex, NULL);
    pthread_mutex_init(&philo->eat_last, NULL);
    //pthread_mutex_init(philo->philo_data->print, NULL);
    
    return (0);
}

int init_philo_forks(t_philo *philo)
{
    int i;

    i = 0;
    philo->forks = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t) * philo->num_of_philo);
    while(i < philo->num_of_philo)
    {
        pthread_mutex_init(&philo->forks[i], NULL);
        i++;
    }
    return (0);
}