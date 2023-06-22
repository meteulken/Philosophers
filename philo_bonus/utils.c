/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:21:53 by mulken            #+#    #+#             */
/*   Updated: 2023/06/13 13:21:54 by mulken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

unsigned int	unsigned_atoi(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = -1;
	if (!str || str[i] < 0)
		return (0);
	while (str[++i])
		res = (res * 10) + (str[i] - '0');
	return (res);
}

int	err_msg(char *msg)
{
	printf("%s", msg);
	return (0);
}

void	print_dead(t_philo *philo, char *str)
{
	sem_wait(philo->table->is_dying);
	printf("%llu %llu %s\n", time_from_start(philo->table), philo->id, str);
}

void	print(t_philo *philo, char *str)
{
	sem_wait(philo->table->is_printing);
	if (!philo->table->stop)
		printf("%llu %llu %s\n", time_from_start(philo->table), philo->id, str);
	sem_post(philo->table->is_printing);
}