/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:23:58 by mulken            #+#    #+#             */
/*   Updated: 2024/01/30 09:07:10 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"
#include "./mallocCollector/mallocCollector.h"

int argument_control(char *argv[])
{
    int i;
    int j;

    i = 1;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if(argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
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

void print_philo(t_philo_data *philo_data, char *str, t_philo *philo)
{
    pthread_mutex_lock(philo->print);
    printf("%llu %d %s\n", time_from_start(philo_data->philo), philo_data->id, str);
    pthread_mutex_unlock(philo->print);
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
    //pthread_mutex_init(philo->philo_data->print, NULL);
    
    return (0);
}
int init_philo_data_helper(t_philo *philo)
{
    int i = 0;
    while(i < philo->num_of_philo)
    {
        philo->philo_data[i].philo = philo;
        philo->philo_data[i].id = i + 1;
        philo->philo_data[i].time_to_die = philo->time_to_die;
        philo->philo_data[i].time_to_eat = philo->time_to_eat;
        philo->philo_data[i].time_to_sleep = philo->time_to_sleep;
        philo->philo_data[i].time_to_start = philo->start_time;
        philo->philo_data[i].must_eat = philo->eat_count;
        i++;
    }
    return (0);
}

void *philo_die_control(void *arg)
{
    int i;
    t_philo *philo;
    philo = (t_philo *)arg;
    uint64_t time;
    

    i = 0;
    while(i < philo->num_of_philo)
    {
        //pthread_mutex_lock(philo->die);
        time = get_time_for_philo();
        if(time - philo->philo_data[i].start_time > philo->time_to_die)
        {
            print_philo(&philo->philo_data[i], "died", philo);
            philo->is_dead = 1;
            return (NULL);
        }
        //pthread_mutex_unlock(philo->die);
    }
    return (NULL);
}

void *philo_routine(void *arg)
{
    t_philo_data *philo_data;
    philo_data = (t_philo_data *)arg;
    printf("->%d\n", philo_data->must_eat);
    
    if(philo_data->id % 2 == 0)
        ft_usleep(200);
    while(philo_data->philo->is_dead == 0)
    {
        if(philo_data->must_eat != -1)
            philo_data->must_eat--;
        if(philo_data->must_eat == 0)
            break;
        printf("eat->%d\n", philo_data->must_eat);
        pthread_mutex_lock(philo_data->left_fork);
        print_philo(philo_data, "has taken a fork", philo_data->philo);
        pthread_mutex_lock(philo_data->right_fork);
        print_philo(philo_data, "has taken a fork", philo_data->philo);
        print_philo(philo_data, "is eating", philo_data->philo);
        ft_usleep(philo_data->philo->time_to_eat);
        pthread_mutex_unlock(philo_data->left_fork);
        pthread_mutex_unlock(philo_data->right_fork);
        print_philo(philo_data, "is sleeping", philo_data->philo);
        ft_usleep(philo_data->philo->time_to_sleep);
        print_philo(philo_data, "is thinking", philo_data->philo);
        //philo_data->start_time = get_time_for_philo();
        }
    return (NULL);
}

int start_philo(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->num_of_philo)
    {
        pthread_create(&philo->philo_data[i].thread, NULL, &philo_routine, &philo->philo_data[i]);
        i++;
    }
    //pthread_create(&philo->thread2 , NULL, &philo_die_control, philo);
    //printf("philo started\n");
    //pthread_join(philo->thread2, NULL);
    i = 0;
    while(i < philo->num_of_philo)
    {
        pthread_join(philo->philo_data[i].thread, NULL);
        i++;
    }
    return (0);
}

int init_philo_data(t_philo *philo)
{
    int i;

    i = 0;
    philo->forks = (pthread_mutex_t *)new_malloc(philo->mc, sizeof(pthread_mutex_t) * philo->num_of_philo);
    //printf("forks init\n");
    //pthread_mutex_init(philo->die, NULL); !!!!!!!!
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
    
    philo->philo_data[0].left_fork = &philo->forks[philo->num_of_philo - 1];
    philo->philo_data[0].right_fork = &philo->forks[0];
    while (i < philo->num_of_philo)
    {
        philo->philo_data[i].left_fork = &philo->forks[i];
        philo->philo_data[i].right_fork = &philo->forks[i + 1];
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
    philo->is_dead = 0;
    philo->is_eating = 0;
    philo->is_sleeping = 0;
    philo->is_thinking = 0;
    return (0);
}

int main(int argc, char *argv[])
{
    t_philo *philo;
    t_philo_data *philo_data;
    
    if (argc > 6 || argc < 5)
    {
        write(1, "Error: Wrong number of arguments\n", 33);
        return (1);
    }
    if (argument_control(argv))
    {
        write(1, "Error: Arguments must be positive numbers\n", 42);
        return (1);
    }
    philo = (t_philo *)malloc(sizeof(t_philo));
    if (!philo)
    {
        write(1, "Error: t_philo allocation error\n", 32);
        return (1);
    }
    philo->mc = malloc_start();
    philo_data = (t_philo_data *)new_malloc(philo->mc, sizeof(t_philo_data));
    init_philo(philo, argv, argc);
    init_philo_data(philo);
    init_philo_mutex(philo);
    
    init_philo_forks(philo);
    init_philo_data_helper(philo);
    start_philo(philo);
    

    return 0;
}
