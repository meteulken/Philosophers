#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philohead.h"

void* philo_eating(void* arg) {
    philo_d* data = (philo_d*)arg;
    int i = 0;
 
    while (i <= data->time_eat) {
    pthread_mutex_lock(&mutex);
        printf("%d philo eat \n", i);
        usleep(3000);
        i++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* philo_sleep(void* arg) {
    philo_d* data = (philo_d*)arg;

    int i = 0;
    while (i <= data->time_sleep) {
     pthread_mutex_lock(&mutex);
        printf("%d philo sleep \n", i);
        usleep(3000);
        i++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* philo_die(void* arg) {
    philo_d* data = (philo_d*)arg;

    int i = 0;
    while (i <= data->time_die) {
     pthread_mutex_lock(&mutex);
        printf("%d philo die \n", i);
        usleep(3000);
        i++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void philo_init(philo_d* data) {
    pthread_t philo1;
    pthread_t philo2;
    pthread_t philo3;

 pthread_mutex_init(&mutex,NULL);
    pthread_create(&philo1, NULL, philo_eating, (void*)data);
    pthread_create(&philo2, NULL, philo_sleep, (void*)data);
    pthread_create(&philo3, NULL, philo_die, (void*)data);

    pthread_join(philo1, NULL);
    pthread_join(philo2, NULL);
    pthread_join(philo3, NULL);
    
        pthread_mutex_destroy(&mutex);
}

int main(int argc, char* argv[]) {
    
    philo_d data[4];
    int i = 0;
    if (argc >= 4 && argc <= 6) {

        
        data[i].philo_num = atoi(argv[1]);
        data[i].time_eat = atoi(argv[2]);
        data[i].time_sleep = atoi(argv[3]);
        data[i].time_die = atoi(argv[4]);

        philo_init(data);

    }
    else
        printf("wrong argument");
    return 0;
}
