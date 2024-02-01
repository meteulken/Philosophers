/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 07:58:59 by mulken            #+#    #+#             */
/*   Updated: 2024/02/01 07:59:14 by mulken           ###   ########.fr       */
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
        while(i < philo->num_of_philo)
        {
            pthread_mutex_lock(&philo->die);
            pthread_mutex_lock(&philo->sleep);
            time = get_time_for_philo();
            if(time - philo->philo_data[i].time_to_start > philo->time_to_die)
            {
                print_philo(&philo->philo_data[i], "died", philo);
                pthread_mutex_lock(&philo->die_mutex);
                philo->is_dead = 0;
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