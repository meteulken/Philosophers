#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"


void* philo_eating(void* arg) {
    philo_d* data = (philo_d*)arg;
    int i = data->philo_num;

    pthread_mutex_lock(&mutex[i]);
    int j = 0;
    while (j <= data->time_eat) {
        printf("%d philo is eating\n", i);
        usleep(300000);
        j++;
    }
    pthread_mutex_unlock(&mutex[i]);

    return NULL;
}

void* philo_sleep(void* arg) {
    philo_d* data = (philo_d*)arg;
    int i = data->philo_num;

    pthread_mutex_lock(&mutex[i]);
    int j = 0;
    while (j <= data->time_sleep) {
        printf("%d philo is sleeping\n", i);
        usleep(300000);
        j++;
    }
    pthread_mutex_unlock(&mutex[i]);

    return NULL;
}

void* philo_die(void* arg) {
    philo_d* data = (philo_d*)arg;
    int i = data->philo_num;

    pthread_mutex_lock(&mutex[i]);
    int j = 0;
    while (j <= data->time_die) {
        printf("%d philo is die\n", i);
        usleep(300005);
        j++;
    }
    pthread_mutex_unlock(&mutex[i]);

    return NULL;
}

void philo_init(philo_d* data) {
    int i = 0;
    int j = data->philo_num;
    pthread_t philo[j];

    while(i < j) {
        pthread_mutex_init(&mutex[i], NULL);
        i++;
    }
     i = 0;
    while (i < j) {
        data[i].philo_num = i;
        pthread_create(&philo[i], NULL, philo_eating, (void*)&data[i]);
        pthread_create(&philo[i], NULL, philo_sleep, (void*)&data[i]);
        pthread_create(&philo[i], NULL, philo_die, (void*)&data[i]);
        i++;
    }
    i = 0;
    while (i < j) {
        pthread_join(philo[i], NULL);
        i++;
    }
    i = 0;
    while(i < j) {
        pthread_mutex_destroy(&mutex[i]);
        i++;
    }
}

int main(int argc, char* argv[]) {

    philo_d data[4];
    int i = 0;
    if (argc >= 5 && argc <= 6) {

        long long s = delta_time(atoi(argv[2]));
        printf("%lld S\n",s);
        data[i].philo_num = atoi(argv[1]);
        data[i].time_eat = atoi(argv[2]);
        data[i].time_sleep = atoi(argv[3]);
        data[i].time_die = atoi(argv[4]);

        while (i < data[i].philo_num) {
            pthread_mutex_init(&mutex[i], NULL);
            i++;
        }

        philo_init(data);
      i = 0;
        while(i < data[i].philo_num) {
            pthread_mutex_destroy(&mutex[i]);
            i++;
        }
    } else {
        printf("wrong argument");
    }

    return 0;
}
