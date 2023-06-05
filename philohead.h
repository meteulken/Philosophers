#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

pthread_mutex_t mutex;

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

#endif 
