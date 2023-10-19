/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <mulken@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:54:30 by mulken            #+#    #+#             */
/*   Updated: 2023/10/19 23:37:50 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philo)
	{
		if (pthread_create(&env->philos[i].thread, NULL, \
			routine, &env->philos[i]))
		{
			pthread_mutex_lock(&env->m_stop);
			env->stop = 1;
			pthread_mutex_unlock(&env->m_stop);
			return (i);
		}
	}
	die_controller(env);
	return (env->number_of_philo);
}

void	destroy_threads(t_env *env, int thread_count)
{
	int	i;

	i = -1;
	while (++i < thread_count)
		pthread_join(env->philos[i].thread, NULL);
}
