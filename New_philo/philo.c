/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:23:58 by mulken            #+#    #+#             */
/*   Updated: 2024/01/31 09:23:29 by mulken           ###   ########.fr       */
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

int	must_eating_check(t_philo *philo)
{
	int	i;

	if (philo->eat_count < 0)
		return (0);
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_lock(philo->eat);
		if (philo->philo_data[i++].eat_count < philo->eat_count)
		{
			pthread_mutex_unlock(philo->eat);
			return (0);
		}
		else
			pthread_mutex_unlock(philo->eat);
	}
	return (1);
}

int philo_die_control(void *arg)
{
    int i;
    t_philo *philo;
    philo = (t_philo *)arg;
    uint64_t time;

    i = 0;
    while(philo->num_of_philo > 0)
    {
        i = 0;
        //printf("test\n");
        while(i < philo->num_of_philo)
        {
            pthread_mutex_lock(philo->die);
            pthread_mutex_lock(philo->sleep);
            time = get_time_for_philo();
            if(time - philo->philo_data[i].time_to_start > philo->time_to_die)
            {
                print_philo(&philo->philo_data[i], "died", philo);
                pthread_mutex_lock(&philo->die_mutex);
                philo->is_dead = 0;
                pthread_mutex_unlock(&philo->die_mutex);
                pthread_mutex_unlock(philo->die);
                return (0);
            }
            else
                pthread_mutex_unlock(philo->sleep);
            pthread_mutex_unlock(philo->die);
            i++;
        }
        if (must_eating_check(philo)) // !!!!!!!!!
			break ;
    }
    return (1);
}

void philo_eat(t_philo_data *philo_data)
{
    pthread_mutex_lock(philo_data->right_fork);
    print_philo(philo_data, "has taken a fork", philo_data->philo);
    pthread_mutex_lock(philo_data->left_fork);
    print_philo(philo_data, "has taken a fork", philo_data->philo);
    print_philo(philo_data, "is eating", philo_data->philo);
    pthread_mutex_lock(philo_data->philo->eat);
    philo_data->eat_count++;
    pthread_mutex_unlock(philo_data->philo->eat);
    ft_usleep(philo_data->philo->time_to_eat);
    pthread_mutex_lock(philo_data->philo->sleep);
    philo_data->time_to_start = get_time_for_philo();
    pthread_mutex_unlock(philo_data->philo->sleep);
    pthread_mutex_unlock(philo_data->left_fork);
    pthread_mutex_unlock(philo_data->right_fork);
}

void philo_sleep(t_philo_data *philo_data)
{
    print_philo(philo_data, "is sleeping", philo_data->philo);
    ft_usleep(philo_data->philo->time_to_sleep);
}

void philo_think(t_philo_data *philo_data)
{
    print_philo(philo_data, "is thinking", philo_data->philo);
}


void *philo_routine(void *arg)
{
    t_philo_data *philo_data;
    philo_data = (t_philo_data *)arg;
    int check;
    check = 1;
    
    if(philo_data->id % 2 == 0)
        ft_usleep(10);
    while(check)
    {
        pthread_mutex_lock(&philo_data->philo->die_mutex);
        check = philo_data->philo->is_dead;
        pthread_mutex_unlock(&philo_data->philo->die_mutex);
        if(check == 0)
            break;
		philo_eat(philo_data);
		philo_sleep(philo_data);
		philo_think(philo_data);
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
    //philo_die_control(philo);
    //pthread_create(&philo->thread2 , NULL, &philo_die_control, philo);
    //printf("philo started\n");
    //pthread_join(philo->thread2, NULL);
    if(!philo_die_control(philo))
    {
        pthread_mutex_lock(&philo->die_mutex);
        philo->is_dead = 0;
        pthread_mutex_unlock(&philo->die_mutex);
    }
    return (0);
}



int main(int argc, char *argv[])
{
    t_philo *philo;
    t_philo_data *philo_data;
    (void)philo_data;
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
    philo_data = (t_philo_data *)new_malloc(philo->mc, sizeof(t_philo_data) * philo->num_of_philo);
    init_philo(philo, argv, argc);
    init_philo_data(philo);
    init_philo_mutex(philo);
    
    init_philo_forks(philo);
    init_philo_data_helper(philo);
    start_philo(philo);

    int i = 0;
    while(i < philo->num_of_philo)
    {
        pthread_join(philo->philo_data[i].thread, NULL);
        i++;
    }
    return 0;
}
