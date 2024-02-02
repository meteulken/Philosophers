/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:58:59 by mulken            #+#    #+#             */
/*   Updated: 2024/02/02 17:43:00 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	must_eating_check(t_philo *philo)
{
	int	i;

	if (philo->eat_count < 0)
		return (0);
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_lock(&philo->eat);
		if (philo->philo_data[i++].eat_count < philo->eat_count)
		{
			pthread_mutex_unlock(&philo->eat);
			return (0);
		}
		else
			pthread_mutex_unlock(&philo->eat);
	}
	return (1);
}

int philo_die_control(t_philo *philo)
{
    int i;
    uint64_t time;

    i = 0;
    while(philo->num_of_philo > 0)
    {
        i = 0;
        while(i < philo->num_of_philo)
        {
            pthread_mutex_lock(&philo->die);
            pthread_mutex_lock(&philo->sleep);
            time = get_time_for_philo();
            if(time - philo->philo_data[i].time_to_start > philo->time_to_die)
            {
                print_philo(&philo->philo_data[i], "died", philo);
                pthread_mutex_lock(&philo->die_mutex);
                philo->philo_data->philo->is_dead = 0;
                pthread_mutex_unlock(&philo->die_mutex);
                pthread_mutex_unlock(&philo->die);
                return (0);
            }
            else
                pthread_mutex_unlock(&philo->sleep);
            pthread_mutex_unlock(&philo->die);
            i++;
        }
        if (must_eating_check(philo))
			break ;
    }
    return (1);
}

int philo_die_all(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->num_of_philo)
    {
        if (philo->num_of_philo == 1)
			pthread_detach(philo->philo_data[i].thread);
        pthread_join(philo->philo_data[i].thread, NULL);
        i++;
    }
    pthread_mutex_destroy(&philo->print);
    pthread_mutex_destroy(&philo->eat);
    pthread_mutex_destroy(&philo->sleep);
    pthread_mutex_destroy(&philo->think);
    pthread_mutex_destroy(&philo->die);
    pthread_mutex_destroy(&philo->die_mutex);
    pthread_mutex_destroy(&philo->eat_last);
    i = 0;
    while(i < philo->num_of_philo)
    {
        pthread_mutex_destroy(&philo->forks[i]);
        i++;
    }
    return (0);
}
