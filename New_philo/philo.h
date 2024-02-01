/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:24:01 by mulken            #+#    #+#             */
/*   Updated: 2024/02/01 08:38:06 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "./mallocCollector/mallocCollector.h"

typedef struct s_philo_data 
{
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int id;
    pthread_t thread;
    u_int64_t time_to_start;
    int must_eat;
    int eat_count;
    int philo_die;
    struct s_philo *philo;
}t_philo_data;

typedef struct s_philo 
{
    int num_of_philo;
    u_int64_t time_to_die;
    u_int64_t time_to_eat;
    u_int64_t time_to_sleep;
    u_int64_t start_time;
    int must_eat;
    int eat_count;
    int is_dead;
    int is_eating;
    int is_sleeping;
    int is_thinking;
    t_philo_data *philo_data;
    pthread_mutex_t print;
    pthread_mutex_t die;
    pthread_mutex_t die_mutex;
    pthread_mutex_t eat_last;
    pthread_mutex_t eat;
    pthread_mutex_t sleep;
    pthread_mutex_t think;
    pthread_mutex_t *forks;
    pthread_t thread;
    t_mallocCollector *mc;
}t_philo;


int	ft_atoi(const char *nptr);
int get_time_for_philo();
int argument_control(char *argv[]);
int init_philo_forks(t_philo *philo);
int init_philo_mutex(t_philo *philo);
int init_philo_data_helper(t_philo *philo);
int init_philo_data(t_philo *philo);
int init_philo(t_philo *philo, char *argv[], int argc);
int ft_usleep(u_int64_t t);
void *philo_routine(void *arg);
uint64_t	time_from_start(t_philo *philo);
int get_time_for_philo();
void print_philo(t_philo_data *philo_data, char *str, t_philo *philo);
int start_philo(t_philo *philo);
int philo_die_control(t_philo *philo);
int philo_die_all(t_philo *philo);

#endif