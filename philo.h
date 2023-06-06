#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

//pthread_mutex_t fork_l, fork_r;
pthread_mutex_t mutex[4];

typedef struct Philo_data{

	int philo_num;
	int time_eat;
	int time_die;
	int time_sleep;
	int died;

}philo_d;

typedef struct Philo_table{

	pthread_t thread; 


}philo_t;

long long	delta_time(long long time);
long timeG(int timex);
int ft_atoi(char *str);
void* philo_eating(void* arg);
void* philo_sleep(void* arg);
void* philo_die(void* arg);
void philo_init(philo_d* data);


#endif
